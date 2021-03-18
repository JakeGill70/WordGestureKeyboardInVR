from distutils.core import setup
import py2exe

from base64 import decodebytes
import paramiko
import pysftp
import os
import getpass
import datetime

includes = ["base64", "paramiko", "pysftp", "os", "sys", "getpass", "datetime", "_cffi_backend"]
dist_dir = "./up/"

options = {"py2exe":{
    "includes": includes,
    "dist_dir": dist_dir
    }}

setup(name="uploader",
      console=['uploader.py'],
      version="1.0",
      author="Jake Gillenwater",
      author_email="gillenwaterj@etsu.edu",
      url="http://jakegillenwater.dev",
      options=options
      )