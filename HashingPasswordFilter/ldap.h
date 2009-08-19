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

#ifndef _LDAP_H_
#define _LDAP_H_


#define LDAP_SERVER_NAME L"localhost"
//Modify these before compiling
//DN and password of user to log toActive directory
#define LDAP_ADMIN_BIND_DN L"CN=Pippo Pippo,CN=Users,DC=server2003,DC=inginf,DC=units,DC=it"
#define LDAP_ADMIN_PASSWD L"pippo"
//LDAP query to used to find users
#define LDAP_SEARCH_BASE_DN L"CN=Users,DC=server2003,DC=inginf,DC=units,DC=it"
#define USER_SEARCH_QUERY L"sAMAccountName=%s"

bool writeHashToLdap(wchar_t *username,wchar_t *passwordHash);

#endif