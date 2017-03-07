#include <iostream>

#include "cfgutil.h"
#include "INIReader.h"

using namespace std;

inline int _open_ini(const char* inifn)
{
    INIReader ini(inifn);
    if (ini.ParseError() < 0) {
        cout << "cannot load:" << inifn << endl;
        return -1;
    }
    return 0;
}

int get_rootdir_filelist(const char* inifn,
    std::vector<std::string>& filelist,
    std::vector<int>& fileidlist)
{
    int dirno, fileno, totalsize;
    int ret = get_rootdir_info(inifn, &dirno, &fileno, &totalsize);

    if ( ret != 0) {
        return -1;
    }

    string fn;
    int fid;

    //cout << "file ==========>" << endl;
    for (int i = 0; i < fileno; i++) {
        get_rootdir_filename(inifn, i, fn, &fid);
        //cout << i << ":" << fn << "\t" << fid << endl;
        filelist.push_back(fn);
        fileidlist.push_back(fid);
    }

    return 0;
}

int get_rootdir_folderlist(const char* inifn,
    std::vector<std::string>& folderlist,
    std::vector<int>& folderidlist)
{
    int dirno, fileno, totalsize;
    int ret = get_rootdir_info(inifn, &dirno, &fileno, &totalsize);

    if ( ret != 0) {
        return -1;
    }

    string folder_name;
    int folderid;

    //cout << "file ==========>" << endl;
    for (int i = 0; i < dirno; i++) {
        get_rootdir_foldername(inifn, i, folder_name, &folderid);
        //cout << i << ":" << fn << "\t" << fid << endl;
        folderlist.push_back(folder_name);
        folderidlist.push_back(folderid);
    }

    return 0;
}

int get_foldername_from_folderid2(const char* inifn, int folder_id,
        std::string& folder_name)
{
    INIReader ini(inifn);
    if (ini.ParseError() < 0) {
        cout << "cannot load:" << inifn << endl;
        return -1;
    }
    // will not include rootdir
    bool matched = false;
    string matched_group;
    int no_folder = ini.GetInteger("General", "size", 0);
    for (int i=0; i<no_folder; i++) {
        std::string key_name = "folder" + std::to_string(i);
        std::string folder_name = ini.Get("General", key_name, "null");
        key_name = "folderid" + std::to_string(i);
        int fid = ini.GetInteger("General", key_name, 0);

        if (fid == folder_id) {
            matched = true;
            matched_group = "folder" + std::to_string(i);
            //cout << "matched =====> ";
            //cout << folder_name << ":" << fid << endl;
            break;
        }
    }

    if (!matched) {
        return -1;
    }

    folder_name = ini.Get(matched_group, "foldername", "null");
    return 0;
}


int get_foldername_from_folderid(const char* inifn, int folder_id,
        std::string& folder_name)
{
    INIReader ini(inifn);
    if (ini.ParseError() < 0) {
        cout << "cannot load:" << inifn << endl;
        return -1;
    }

    std::string id_name = std::to_string(folder_id);
    folder_name = ini.Get("folderid", id_name, "null");
    return 0;
}

int get_filename_from_fileid(const char* inifn, int file_id,
        std::string& file_name)
{
    INIReader ini(inifn);
    if (ini.ParseError() < 0) {
        cout << "cannot load:" << inifn << endl;
        return -1;
    }

    std::string id_name = std::to_string(file_id);
    file_name = ini.Get("fileid", id_name, "null");
    return 0;
}

int get_filelist_from_folderid(const char* inifn, int folder_id,
        std::vector<std::string>& filelist)
{
    INIReader ini(inifn);
    if (ini.ParseError() < 0) {
        cout << "cannot load:" << inifn << endl;
        return -1;
    }

    filelist.clear();

    // will not include rootdir
    bool matched = false;
    string matched_group;
    int no_folder = ini.GetInteger("General", "size", 0);
    for (int i=0; i<no_folder; i++) {
        std::string key_name = "folder" + std::to_string(i);
        std::string folder_name = ini.Get("General", key_name, "null");
        key_name = "folderid" + std::to_string(i);
        int fid = ini.GetInteger("General", key_name, 0);

        if (fid == folder_id) {
            matched = true;
            matched_group = "folder" + std::to_string(i);
            //cout << "matched =====> ";
            //cout << folder_name << ":" << fid << endl;
            break;
        }
    }

    if (!matched) {
        return -1;
    }

    // load group folderXXX
    int size = ini.GetInteger(matched_group, "size", 0);
    for (int i=0; i<size; i++) {
        std::string fn = ini.Get(matched_group, std::to_string(i), "null");
        filelist.push_back(fn);
    }

    return 0;
}

int get_rootdir_info(const char* inifn, int* dirno, int* fileno, int* totalsize)
{
    INIReader ini(inifn);

    if (ini.ParseError() < 0) {
        cout << "cannot load:" << inifn << endl;
        return -1;
    }

    *dirno = ini.GetInteger("rootdir", "dirno", 0);
    *fileno = ini.GetInteger("rootdir", "fileno", 0);
    *totalsize = ini.GetInteger("rootdir", "totalsize", 0);

    return 0;
}

int get_rootdir_filename(const char* inifn, int idx,
    std::string& fn, int* fileid)
{
    INIReader ini(inifn);

    if (ini.ParseError() < 0) {
        cout << "cannot load:" << inifn << endl;
        return -1;
    }

    string key_name = "f" + std::to_string(idx);
    //cout << "key_name:" << key_name << endl;
    fn = ini.Get("rootdir", key_name, "null");

    key_name = "fileid" + std::to_string(idx);
    *fileid = ini.GetInteger("rootdir", key_name, -1);

    return 0;
}


int get_rootdir_foldername(const char* inifn, int idx,
    std::string& fn, int* dirid)
{
    INIReader ini(inifn);
    if (ini.ParseError() < 0) {
        cout << "cannot load:" << inifn << endl;
        return -1;
    }

    string key_name = "folder" + std::to_string(idx);
    //cout << "key_name:" << key_name << endl;
    fn = ini.Get("rootdir", key_name, "null");

    key_name = "folderid" + std::to_string(idx);
    *dirid = ini.GetInteger("rootdir", key_name, -1);

    return 0;
}

int get_base_dirid(const char* inifn, int* base_dirid)
{
    INIReader ini(inifn);
    if (ini.ParseError() < 0) {
        cout << "cannot load:" << inifn << endl;
        return -1;
    }
    *base_dirid = ini.GetInteger("thread", "BASE_DIRID", 0);
    return 0;
}

int get_base_fileid(const char* inifn, int* base_fileid)
{
    INIReader ini(inifn);
    if (ini.ParseError() < 0) {
        cout << "cannot load:" << inifn << endl;
        return -1;
    }
    *base_fileid = ini.GetInteger("thread", "BASE_FILEID", 0);
    return 0;
}

int is_valid_file_uid(const char* inifn, int uid)
{
    INIReader ini(inifn);
    if (ini.ParseError() < 0) {
        cout << "cannot load:" << inifn << endl;
        return -1;
    }
    int base_fileid = ini.GetInteger("thread", "BASE_FILEID", 0);
    int fileid_size = ini.GetInteger("fileid", "size", 0);

    if (uid >= base_fileid && uid < base_fileid + fileid_size) {
        return 1;
    } else {
        return 0;
    }
}

int is_valid_folder_uid(const char* inifn, int uid)
{
    INIReader ini(inifn);
    if (ini.ParseError() < 0) {
        cout << "cannot load:" << inifn << endl;
        return -1;
    }
    int base_folderid = ini.GetInteger("thread", "BASE_DIRID", 0);
    int folderid_size = ini.GetInteger("General", "size", 0);

    if (uid >= base_folderid && uid < base_folderid + folderid_size) {
        return 1;
    } else {
        return 0;
    }
}

int is_rootdir_uid(const char* inifn, int uid)
{
    int base_dirid = 0;
    if ( get_base_dirid(inifn, &base_dirid) != 0 ) {
        return -1;
    }
    if (uid == base_dirid) {
        return 1;
    } else {
        return 0;
    }
}