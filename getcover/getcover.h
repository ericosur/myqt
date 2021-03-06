/**
 * \file getcover.h
 * \brief header file for class GetCover
 */
#ifndef __GET_COVER_H__
#define __GET_COVER_H__

#include <QString>
#include <QSettings>

#include "handleopt.h"

class GetCover
{
public:
    static QString get_hash_filename(const QString& fn);
    static bool getcover(const QString& mp3fn, QString& tbfn);
    static bool isFileExisted(const QString& fn);
    static void setWriteTb(bool b);

    /** \brief GetCover::setFollowImageType()
        if set to true, thumbnail will be saved
        as the same type within media file
        if set to false, thumbnail is always
        png format, default false
        \param b [in] true will follow thumbnail image type, false always PNG
        \note thumbnail fn extension is always png
        but it could be jpg format
    **/
    static void setFollowImageType(bool b);
    static void setResizeTb(bool b);
    static void show_toggles();
    static void showInfo(const QString& fn);
    static QString getTablibVersion();

protected:
    GetCover(); // not welcome to have instance

    static QString md5sum(const char* buffer, int size);
    static bool extract_cover_from_mp3(const QString& fn, QString& tbfn);
    static bool extract_cover_from_mp4(const QString& fn, QString& tbfn);
    static bool extract_cover_from_flac(const QString& fn, QString& tbfn);
    static bool extract_info_from_mp3(const QString& fn);
    static bool extract_info_from_mp4(const QString& fn);
    static bool extract_info_from_flac(const QString& fn);
    static int extract_length_from_mp3(const QString& fn);
    static int extract_length_from_mp4(const QString& fn);
    static int extract_length_from_flac(const QString& fn);

    static void save_hash(const QString& hash);
    static QString load_hash();
    static QString get_thumb_name(const QString& hstr);
    static bool save_thumbnail(const QImage& img, QString& tbfn, bool isJpeg);

    static void show_aat(const QString& artist, const QString& album, const QString& title);

private:
	// default true
	static bool m_writetb;
	static bool m_followtype;
    static bool m_resizetb;
};

#endif  // __GET_COVER_H__
