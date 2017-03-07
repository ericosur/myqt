#ifndef __CFG_UTIL_H__
#define __CFG_UTIL_H__

#include <string>
#include <vector>

// return 0 if success, -1 if fail
// get rootdir info
// dirno: number of folder items (maybe == 0)
// fileno: number of file items (maybe == 0)
// totalsize: number of all items (folder + file), MUST be equal
// to dirno + fileno
// if dirno, fileno, totalsize = -1, something error ...
int get_rootdir_info(const char* inifn, int* dirno, int* fileno, int* totalsize);

// you need call get_rootdir_info() to know max no of filename
// assign ini filename
// assign rootdir file idx
// return fn for fullpath filename
// return fileid for unique file id
int get_rootdir_filename(const char* inifn, int idx, std::string& fn, int* fileid);

// you need call get_rootdir_info() to know max no of folders
// assign ini filename
// assign rootdir folder idx
// return fn for full path folder
// return folderid for unique folder id
int get_rootdir_foldername(const char* inifn, int idx, std::string& fn, int* folderid);


// no need to call get_rootdir_info()
// given inifn for ini path
// data stored at filelist and fileidlist
// will return file list (fullpath) in rootdir
// and unique id of files in rootdir
int get_rootdir_filelist(const char* inifn,
    std::vector<std::string>& filelist,
    std::vector<int>& fileidlist);

// no need to call get_rootdir_info()
// given inifn for ini path
// data stored at folderlist and folderidlist
// will return folderlist (fullpath) in rootdir
// and unique id of folders in rootdir
int get_rootdir_folderlist(const char* inifn,
    std::vector<std::string>& folderlist,
    std::vector<int>& folderidlist);

// input ini filenmae, and unique folder id
// store at filelist, fullpath filename within this folder
//
int get_filelist_from_folderid(const char* inifn, int folder_id,
        std::vector<std::string>& filelist);


// input inifn
// input file uid
// output folder_name, the fullpath of related folder uid
//
// return -1 if error
// also need check if name == "null"
int get_foldername_from_folderid(const char* inifn, int folder_id,
        std::string& folder_name);

// input inifn
// input file uid
// output file_name, the fullpath of related file uid
//
// return -1 if error
// also need check if file name == "null"
int get_filename_from_fileid(const char* inifn, int file_id,
        std::string& file_name);


int get_base_dirid(const char* inifn, int* base_dirid);
int get_base_fileid(const char* inifn, int* base_fileid);

// input inifn
// input uid to check
// return -1 if error
// return 1 if it is a valid file uid
// return 0 if it is an invliad file uid
//
int is_valid_file_uid(const char* inifn, int uid);
int is_valid_folder_uid(const char* inifn, int uid);

// check if input uid is rootdir
//
// input inifn
// input uid to check
// return -1 if error
// return 1 if it is a valid rootdir uid
// return 0 if it is NOT rootdir uid
//
int is_rootdir_uid(const char* inifn, int uid);

#endif  // __CFG_UTIL_H__
