This projects enable one way password synchronization between a local active directory server and a google apps directory.

Installation

Information required:

• User name and password of a local, non Administrator, account on the active directory machine (syncAppUser)
• User name and password of an account with read privilege of the Active directory and write privilege of the custom field “hashedPassword” of the user entries. This privilege can be given sing the “Delegate controls” wizard of the Active Directory Users and Computers" mmc snapin
• User name and password of an administrator account of google apps (appsAdminUser)
• Path to install to the synchronization application (syncAppPath)
Compilation
• Install Google Data API (http://code.google.com/p/google-gdata/downloads/list)
• Register inside the GAC the following assembly:
  o Google.GData.Apps.dll
  o Google.GData.Client.dll
  o Google.GData.Extensions.dll
  Using the following command line"gacutil /i filename"
• Rebuild the solution

Installation steps:

• Using AD schema editor create the attribute "hashedPassword" of type "Case Sensitive String" and add it as an optional field to the “user” class
• Copy the filter (HashingPasswordFilter.dll) in c:\windows
• Register the filter by adding the following key to the registry
  o [HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Lsa]
  o "Notification Packages"="HashingPasswordFilter" (without the .dll)
• Create the aforementioned users and add the following special permission to syncAppUser
  o Allow Log On Locally
  o Log on as a batch job
• Copy the accluded ini to the ProgramData folder ("C:\Documents and Settings\All Users\Application Data" under windows server 2003)
• Modify the copy of the ini file with your data
• Make it readable only by administrators account
• Copy GoogleHashUpdater.exe in syncAppPath and change permissions to allow execution by syncAppUser
• Activate the option "User must change password at next logon" for all the accounts to sync
• Restart the machine
• Check the installation by looking inside the filter log (C:\Documents and Settings\All Users\Application Data\HashingPasswordFilter.log)

TODO in future versions

Write an installer
