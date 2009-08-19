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

#ifndef _PROCESS_H_
#define _PROCESS_H_

//Modify these before compiling
//Your google apps domain
#define APPS_DOMAIN L"yourdomain.com"
//User and password of admin account of google apps
#define APPS_ADMIN L"admin@yourdomain.com"
#define APPS_PASSW L"yourpass"
//user and password of local account used to run the sync program
#define PROCESS_USER L"pippo"
#define PROCESS_PASSW L"pippo"
//sync program path MUST be absolute
#define PROCESS_COMMAND_PATH L"\"C:\\Documents and Settings\\Administrator\\My Documents\\Visual Studio 2008\\Projects\\HashingPasswordFilter\\Debug"
#define PROCESS_COMMAND_LIST_SUFFIX L"\\GoogleHashUpdater.exe\" %s %s \"%s\" \"%s\" %s SHA-1"
#define PROCESS_COMMAND_LIST PROCESS_COMMAND_PATH PROCESS_COMMAND_LIST_SUFFIX

bool sendHashToChildProcess(wchar_t *username,wchar_t *passwordHash, wchar_t* impersonatingUser, wchar_t* impersonatingPassword);

#endif