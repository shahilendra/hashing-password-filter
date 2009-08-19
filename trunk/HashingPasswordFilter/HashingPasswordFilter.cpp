/**
 *
 * Copyright (c) 2009 Mauri Marco All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#include "stdafx.h"
extern "C"{
#include "sha1.h"
}


   #ifndef STATUS_SUCCESS
   #define STATUS_SUCCESS                  ((NTSTATUS)0x00000000L)
   #define STATUS_OBJECT_NAME_NOT_FOUND    ((NTSTATUS)0xC0000034L)
   #define STATUS_INVALID_SID              ((NTSTATUS)0xC0000078L)
   #endif




BOOLEAN NTAPI InitializeChangeNotify();
NTSTATUS NTAPI PasswordChangeNotify(PUNICODE_STRING,ULONG,PUNICODE_STRING);
BOOLEAN NTAPI PasswordFilter(PUNICODE_STRING,PUNICODE_STRING,PUNICODE_STRING,BOOLEAN);

//This method calculate the SHA-1 hash of the given password
//password must be a null terminated string
//hash must be a preallocated buffer of at least 41 characters (40 character + null)
void hashPassword(char* password, wchar_t * hash){
	SHA1Context sha;
	SHA1Reset(&sha);
	SHA1Input(&sha, (const unsigned char *) password, strlen(password));
	if (!SHA1Result(&sha)){
		hash = NULL;
		return;
	}
	for(int i = 0; i < 5 ; i++)
	{
		swprintf(&hash[i*8],9,L"%.8x",sha.Message_Digest[i]);
	}
}

//no initialization necessary
BOOLEAN NTAPI InitializeChangeNotify()
{
    writeLog(L"HashingPasswordFilter initialized");
    return TRUE;
}


//the event: password has changed succesfully
NTSTATUS NTAPI PasswordChangeNotify(PUNICODE_STRING UserName,ULONG RelativeId,PUNICODE_STRING NewPassword)
{
		
	int nLen=0;
    bool result;
	
    //copy username
    int userLength = UserName->Length/ sizeof(wchar_t);
    wchar_t* username = (wchar_t*)malloc((userLength + 1) * sizeof(wchar_t));
    wchar_t* z = wcsncpy(username,UserName->Buffer,userLength);
    //set the last character to null
    username[userLength] = NULL;

	//convert the password from widechar to utf-8
    int passwordLength = NewPassword->Length/ sizeof(wchar_t);
	nLen = WideCharToMultiByte(CP_UTF8, 0, NewPassword->Buffer, passwordLength, 0, 0, 0, 0);
    char* password = (char*)malloc((nLen + 1) * sizeof(char));
	nLen = WideCharToMultiByte(CP_UTF8, 0, NewPassword->Buffer,passwordLength, password, nLen, 0, 0);
    //set the last character to null
    password[nLen] = NULL;

	//allocate and calculate the hash
    wchar_t hash[41];
	hashPassword(password,hash);
    //try to write the hash to ldap
	result = writeHashToLdap(username,hash);
    if (result)
        writeMessageToLog(CHANGE_PASSWORD_MESSAGE,username);
    else
        writeMessageToLog(L"Change failed for user \"%s\"",username);
    //try to write the hash to google apps trough an helper app
    sendHashToChildProcess(username,hash,PROCESS_USER,PROCESS_PASSW);


    //zero the password
    SecureZeroMemory(password,nLen);
    //free the memory
	free(username);
	free(password);

    
    //can I return something else in case of error?
	return STATUS_SUCCESS;

}

//don't apply any password policy
BOOLEAN NTAPI PasswordFilter(PUNICODE_STRING AccountName,PUNICODE_STRING FullName,PUNICODE_STRING Password,BOOLEAN SetOperation)
{

   return TRUE;

}
