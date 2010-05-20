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

using System;
using System.IO;
using System.Collections.Generic;
using System.Text;
using System.Net;
using Google.GData.Apps;
using Google.GData.Client;

namespace GoogleHashUpdater
{
    class Program
    {
        private static StreamWriter log = null;

        private static void Log(String message)
        {
            DateTime now = DateTime.UtcNow;

            log.WriteLine(now.ToString("[yyyy/MM/dd hh:mm:ss:fff] ") + message);
        }

        /*
         * parameters:
         * domain, admin, adminPassword, user, hash, hashFunction, proxyAddress, proxyUser, proxyPassword
         */
        static void Main(string[] args)
        {
            //Open the log file
            string applicationDataDirectory = Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData);
            string logPath = Path.Combine(applicationDataDirectory, "GoogleHashUpdater.log");
            log = new StreamWriter(logPath, true);
            try
            {
                if (args.Length < 6)
                {
                    //wrong number of argument, exit
                    Log("Program called with an incurrect number of arguments");
                    Environment.ExitCode = 10;
                    return;
                }
                //Connect to google apps
                String domain = args[0];
                String admin = args[1];
                String adminPassword = args[2];
                String user = args[3];
                String hash = args[4];
                String hashFunction = args[5];
                
                AppsService service = new AppsService(domain, admin, adminPassword);
                
                //proxy settings
                if (args.Length >= 7)
                {
	                GDataRequestFactory requestFactory = (GDataRequestFactory) service.CreateRequestFactory();
	                WebProxy myProxy = new WebProxy(args[6], true); // format: http://192.168.0.1:8080/
					//setup credentials on the proxy here
					if (args.Length == 9)
					{
						myProxy.Credentials = new NetworkCredential(args[7], args[8]);
					}
					else
					{
						myProxy.Credentials = CredentialCache.DefaultCredentials;
					}
					requestFactory.Proxy = myProxy;
					service.SetRequestFactory(requestFactory);
                }
				
                try
                {
                    //Search the user
                    UserEntry entry = service.RetrieveUser(user);
                    //change the pasword
                    entry.Login.Password = hash;
                    entry.Login.HashFunctionName = hashFunction;
                    //save modification
                    entry.Update();
                }
                catch (LoggedException ex)
                {
                    //On error log and close
                    Log("Failed to update password: " + ex.Message);
                    Environment.ExitCode = 20;
                    return;
                }
                //on succes log and close
                Log(String.Format("Changed password for user \"{0}\"", user));
            }          
            finally
            {
                log.Close();
            }
        }
    }
}
