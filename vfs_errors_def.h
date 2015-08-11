// Contains error strings to be used in VFS exceptions

#ifndef VFS_ERRORS_DEF_H
#define VFS_ERRORS_DEF_H

// general errors
const char *VFS_GEN_01 = "VFS_ERROR: Repository not open";

// create
const char *VFS_CREATE_01 = "VFS_CREATE: Unable to create host repository";

// open
const char *VFS_OPEN_01 = "VFS_OPEN: Unable to open host repository";

// close
const char *VFS_CLOSE_01 = "VFS_CLOSE: Error during close of host repository";

// makedir
const char *VFS_MAKEDIR_01 = "VFS_MAKEDIR: Parent folder not found";
const char *VFS_MAKEDIR_02 = "VFS_MAKEDIR: Folder already exists";

// list
const char *VFS_LISTDIR_01 = "VFS_LISTDIR: Folder not found";

// copy-in
const char *VFS_COPYIN_01 = "VFS_COPYIN: Destination folder not found in VFS";
const char *VFS_COPYIN_02 = "VFS_COPYIN: Destination file already exists in VFS";
const char *VFS_COPYIN_03 = "VFS_COPYIN: Error accessing source file in host";

// copy-out
const char *VFS_COPYOUT_01 = "VFS_COPYOUT: File not found in VFS";
const char *VFS_COPYOUT_02 = "VFS_COPYOUT: Unable to save file in host";

// cat
const char *VFS_CAT_01 = "VFS_CAT: File not found";

// move
const char *VFS_MOVE_01 = "VFS_MOVE: Source file/folder not found";
const char *VFS_MOVE_02 = "VFS_MOVE: Target file/folder not found";
const char *VFS_MOVE_03 = "VFS_MOVE: Target file already exists";

// delete
const char *VFS_DEL_01 = "VFS_DEL: Source file/folder not found";


#endif

