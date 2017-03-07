#if 0

#include <QtCore>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextCodec>
#include <QDebug>

void test()
{
    QDir dir("./");
    QStringList filter;
    QFile _file;

    filter << "*.*";

    foreach (QString file, dir.entryList(filter, QDir::Files | QDir::NoSymLinks)) {
        QFileInfo _info(dir, file);
        QString _fullpath = _info.filePath();
        qDebug() << QFile::encodeName(_fullpath);

        _file.setFileName(_fullpath);
        if (_file.exists(_fullpath)) {
            qDebug() << "ok";
        } else {
            qDebug() << "not ok:" << _fullpath;
        }
    }
}

void test2()
{
    QTextCodec *locale = QTextCodec::codecForLocale();
    qDebug() << "locale:" << locale->name();
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test();
    test2();
    return 0;
}
#endif

/* Example: parse a simple configuration file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>

#include "cfgutil.h"

using namespace std;

#define INIPATH "/tmp/video_out.ini"

//
// demo to get all items at rootdir
//
void test_list_rootdir()
{
    cout << __func__ << endl;
    int dirno, fileno, totalsize;

    // to know how many folders, files under rootdir
    get_rootdir_info(INIPATH, &dirno, &fileno, &totalsize);
    cout << "dirno: " << dirno << endl
        << "fileno: " << fileno << endl
        << "totalsize: " << totalsize << endl;

    string fn;
    int fid;

    cout << "file ==========>" << endl;
    for (int i = 0; i < fileno; i++) {
        // enum files under rootdir via index
        get_rootdir_filename(INIPATH, i, fn, &fid);
        cout << i << ":" << fn << "\t" << fid << endl;
    }
    cout << "folder ==========>" << endl;
    for (int i = 0; i < dirno; i++) {
        // enum folders under rootdir via index
        get_rootdir_foldername(INIPATH, i, fn, &fid);
        cout << i << ":" << fn << "\t" << fid << endl;
    }
}

void test_list()
{
    cout << __func__ << endl;
    if (true) {
        cout << "files..." << endl;
        std::vector<std::string> filelist;
        std::vector<int> fileidlist;
        // get list of files under rootdir
        get_rootdir_filelist(INIPATH, filelist, fileidlist);

        for (size_t i=0; i<filelist.size(); i++) {
            cout << "[" << fileidlist.at(i) << "]:" << filelist.at(i) << endl;
        }
    }

    if (true) {
        cout << "folders..." << endl;
        std::vector<std::string> folderlist;
        std::vector<int> folderidlist;
        // get list of folders under rootdir
        get_rootdir_folderlist(INIPATH, folderlist, folderidlist);

        for (size_t i=0; i<folderlist.size(); i++) {
            cout << "[" << folderidlist.at(i) << "]:" << folderlist.at(i) << endl;
        }
    }
}

void test_folder()
{
    cout << __func__ << endl;
    const int MAGIC_FOLDER_ID = 6291457;
    const int MAGIC_FILE_ID = 8388609;

    std::vector<string> fl;
    // assign folder id, and retrieve file list in this folder
    get_filelist_from_folderid(INIPATH, MAGIC_FOLDER_ID, fl);
    for (size_t i=0; i<fl.size(); ++i) {
        cout << fl.at(i) << endl;
    }

    string dirn;
    get_foldername_from_folderid(INIPATH, MAGIC_FOLDER_ID, dirn);
    cout << "dirn:" << dirn << endl;

    string ffn;
    get_filename_from_fileid(INIPATH, MAGIC_FILE_ID, ffn);
    cout << "ffn:" << ffn << endl;
}

void test_yesno()
{
    cout << __func__ << endl;
#define yesno(x)  ((x==1) ? "yes" : "no")

    const int MAGIC_FOLDER_ID = 6291457;
    cout << MAGIC_FOLDER_ID << " is valid folder uid? " <<
        yesno( is_valid_folder_uid(INIPATH, MAGIC_FOLDER_ID) ) << endl;
    cout << MAGIC_FOLDER_ID << " is valid file uid? " <<
        yesno( is_valid_file_uid(INIPATH, MAGIC_FOLDER_ID) ) << endl;
    cout << MAGIC_FOLDER_ID << " is valid rootdir uid? " <<
        yesno( is_rootdir_uid(INIPATH, MAGIC_FOLDER_ID) ) << endl;

    int tid = MAGIC_FOLDER_ID - 1;
    cout << tid << " is valid rootdir uid? " <<
        yesno( is_rootdir_uid(INIPATH, tid) ) << endl;

    tid = MAGIC_FOLDER_ID -1 + 0x200000;
    cout << tid << " is valid folder uid? " <<
        yesno( is_valid_folder_uid(INIPATH, tid) ) << endl;
    cout << tid << " is valid file uid? " <<
        yesno( is_valid_file_uid(INIPATH, tid) ) << endl;

    tid = MAGIC_FOLDER_ID -1 + 0x1fffff;
    cout << tid << " is valid folder uid? " <<
        yesno( is_valid_folder_uid(INIPATH, tid) ) << endl;
    cout << tid << " is valid file uid? " <<
        yesno( is_valid_file_uid(INIPATH, tid) ) << endl;

    cout << "-----------\n";
    int basedid;
    get_base_dirid(INIPATH, &basedid);
    cout << basedid << " is valid rootdir uid? " <<
        yesno( is_rootdir_uid(INIPATH, basedid) ) << endl;
    tid = basedid + 1;
    cout << tid << " is valid folder uid? " <<
        yesno( is_valid_folder_uid(INIPATH, tid) ) << endl;
    tid = basedid + 10;
    cout << tid << " is valid folder uid? " <<
        yesno( is_valid_folder_uid(INIPATH, tid) ) << endl;
    tid = basedid + 0x1ffffe;
    cout << tid << " is valid folder uid? " <<
        yesno( is_valid_folder_uid(INIPATH, tid) ) << endl;
    tid = basedid + 0x1fffff;
    cout << tid << " is valid folder uid? " <<
        yesno( is_valid_folder_uid(INIPATH, tid) ) << endl;
    tid = basedid + 0x200000;
    cout << tid << " is valid folder uid? " <<
        yesno( is_valid_folder_uid(INIPATH, tid) ) << endl;

    cout << "-----------\n";
    int basefid;
    get_base_fileid(INIPATH, &basefid);
    cout << basefid << " is valid rootdir uid? " <<
        yesno( is_rootdir_uid(INIPATH, basefid) ) << endl;
    tid = basefid;
    cout << tid << " is valid file uid? " <<
        yesno( is_valid_file_uid(INIPATH, tid) ) << endl;
    tid = basefid + 1;
    cout << tid << " is valid file uid? " <<
        yesno( is_valid_file_uid(INIPATH, tid) ) << endl;
    tid = basefid + 10;
    cout << tid << " is valid file uid? " <<
        yesno( is_valid_file_uid(INIPATH, tid) ) << endl;
    tid = basefid + 50;
    cout << tid << " is valid file uid? " <<
        yesno( is_valid_file_uid(INIPATH, tid) ) << endl;
    tid = basefid + 0x1FFFFF;
    cout << tid << " is valid file uid? " <<
        yesno( is_valid_file_uid(INIPATH, tid) ) << endl;
    tid = basefid + 0x200000;
    cout << tid << " is valid file uid? " <<
        yesno( is_valid_file_uid(INIPATH, tid) ) << endl;

}

int main()
{
    test_list_rootdir();
    cout << "\n\n";
    test_list();
    test_folder();

    test_yesno();
    return 0;
}
