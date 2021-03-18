from base64 import decodebytes
import paramiko
import pysftp
import os
import getpass
import datetime
import sys

resultsPath = sys.argv[1]


def countFiles(localPath):
    return sum([len(files) for root, directories, files in os.walk(localPath, topdown=False)])


def uploadFolder_recursive(sftp, localPath, remotePath, totalFiles=0, filesSoFar=0):
    # Uploads each file in a folder to the server.
    # If a subfolder exists, then each file within it will be added as well
    # This method is recrusive, so it will work with any number of subfolders

    # Store the pwd
    old_pwd = sftp.pwd

    # Change to the new directory
    sftp.chdir(remotePath)

    # Begin copying each file in the local folder
    files = os.listdir(localPath)

    # Update for status messages
    totalFiles += len(files)

    for name in files:
        # Update for status messages
        filesSoFar += 1

        if(filesSoFar % 10 == 0):
            percentComplete = filesSoFar/totalFiles
            percentComplete *= 100
            print(f"Estimated percent complete: {round(percentComplete, 2)}")

        filePathName = localPath + "/" + name
        # If the file is a _really a file_, then upload it
        if(os.path.isfile(filePathName)):
            sftp.put(filePathName)
        else:
            # If the file is _really a folder_, then handle that...
            remoteDirectoryName = remotePath + "/" + name
            # Make the folder on the remote if it doesn't already exists
            if(not sftp.exists(remoteDirectoryName)):
                sftp.mkdir(remoteDirectoryName)
            # Start uploading the files in this subfolder
            uploadFolder_recursive(sftp, filePathName, remoteDirectoryName)

    # Restore the pwd
    sftp.chdir(old_pwd)


print("Establishing security settings...")

# Setup secure connection to the server
keydata = b"""AAAAB3NzaC1yc2EAAAADAQABAAABAQC+FOPklLRQbVlpHH53sVg31MJfwZWLDGkT1PnwLQT2rkbEYPT294zOA2CNv+HbQxQR+DaYKXBEA5ZhpLLwh3QV2t/0gpKvTZDZn1vaBlUnCRbHFKkFQDM1Scj/mmIny+v/u/B06ODvNRoFogUPxpK6mmfzYguaqFTJb4Ty62qnmcXc224Mizs8p0Ms1+YCVW20pR9cd7Oq9RrhaeiDnn2dSP8SRxdJ+5HwDIP6GMUThO56Ysb42xRThP3KbPHHeHelR0rd8Nvrih0CZFn0XGGKoKWxNUrnWO3ap9TMDHOfuvtXXl9ynDdUp7wLJ2dR8DSIwt6MTG9DBVsrTQsPSuyl"""
key = paramiko.RSAKey(data=decodebytes(keydata))
cnopts = pysftp.CnOpts()
cnopts.hostkeys.add('jakegillenwater.dev', 'ssh-rsa', key)

print("Connecting to server...")

# Connect to the server
with pysftp.Connection('jakegillenwater.dev', username='volunteer', password='thesis', cnopts=cnopts) as sftp:

    # Work within the bounds of the given directory
    with sftp.cd('/home/volunteer/dataUploads'):

        print("Finding volunteer directory...")

        # If the user has not uploaded before, then create a directory for them
        userName = getpass.getuser()
        if(not sftp.exists(f"./{userName}")):
            sftp.mkdir(userName)

        # Change directories to this user's specific folder
        sftp.chdir(f"./{userName}")

        # Create a time stamped results folder
        currentDateTime = datetime.datetime.now()
        timeStamp = currentDateTime.strftime("%m-%d-%Y-%H-%M-%S")
        resultsFolderName = "Results-" + timeStamp
        sftp.mkdir(resultsFolderName)
        # Change the remote directory to the new results folder
        sftp.chdir(resultsFolderName)

        print("Uploading files...")

        # Get the full path to the results folder
        # dataPath = os.path.expanduser("~/Documents/WordGestureKeyboard/Results")

        # Upload the results folder
        uploadFolder_recursive(sftp, resultsPath, sftp.pwd)

print("Upload complete!")
input("Press 'Enter' to continue.")
