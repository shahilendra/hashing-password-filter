# Installation #

## Information required: ##

  * User name and password of a non Administrator account on the active directory machine (syncAppUser)
  * User name and password of an account with read privilege of the Active directory and write privilege of the custom field “hashedPassword” of the user entries. This privilege can be given sing the “Delegate controls” wizard of the Active Directory Users and Computers" mmc snapin
  * User name and password of an administrator account of google apps (appsAdminUser)
  * Path to install to the synchronization application (syncAppPath)

## Prerequisites: ##
  * Install Google Data API (http://code.google.com/p/google-gdata/downloads/list)
  * Copy the following files from the Google Data API installation folder to c:\windows\assembly of every domain controller:
    * Google.GData.Apps.dll
    * Google.GData.Client.dll
    * Google.GData.Extensions.dll

## Installation steps: ##
These steps must be repeated o every domain controller

  * Using AD schema editor (see http://www.setup32.com/network-administration/active-directory/modifying-active-directorys-schema.php) create the attribute "hashedPassword" of type "Case Sensitive String" and add it as an optional field to the “user” class
  * Copy the filter (HashingPasswordFilter.dll) in c:\windows
  * Register the filter using the allegated reg file (HashingPasswordFilter.reg)
  * Create the aforementioned users and add the following special permission to syncAppUser using "Domain Controller Security Policy"
    * Allow Log On Locally
    * Log on as a batch job
  * Copy the accluded ini to the ProgramData folder ("C:\Documents and Settings\All Users\Application Data" under windows server 2003)
  * Modify the copy of the ini file with your data
  * Make it readable only by administrators account
  * Copy GoogleHashUpdater.exe in syncAppPath and change permissions to allow execution by syncAppUser
  * Activate the option "User must change password at next logon" for all the accounts to sync
  * Restart the machine
  * Check the installation by looking inside the filter log (C:\Documents and Settings\All Users\Application Data\HashingPasswordFilter.log)