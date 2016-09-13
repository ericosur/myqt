/**
 * \file getcover.cpp
 * \brief implementation for class GetCover
 */
#include "getcover.h"
#include "yoseshm.h"

#include <QImage>
#include <QDebug>
#include <QRegExp>
#include <QFile>
#include <QCryptographicHash>

// taglib headers {
#include <taglib/taglib.h>
#include <taglib/tmap.h>
#include <taglib/tstring.h>
//#include <taglib/tpropertymap.h>
#include <taglib/id3v1tag.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2frame.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/mp4file.h>
#include <taglib/mp4tag.h>
#include <taglib/mp4coverart.h>
// taglib headers }

#define DEFAULT_BUFFER_SIZE     (512)
char buffer[DEFAULT_BUFFER_SIZE];

/// default will output tb
bool GetCover::m_writetb = true;
bool GetCover::m_followtype = false;
bool GetCover::m_resizetb = false;

GetCover::GetCover()
{
}

void GetCover::save_hash(const QString& hash)
{
    qDebug() << Q_FUNC_INFO << "=>" << hash;
    QByteArray arr = hash.toLocal8Bit();
    qDebug() << arr.size() << arr.constData();
    myShm::saveToShm(arr.size(), (const char*)arr.constData());
}
QString GetCover::load_hash()
{
    QString ret = "";

    uint32_t size = 0;
    myShm::readFromShm(size, buffer);
    QByteArray arr((char*)buffer, (int)size);
    ret.append(arr);
    return ret;
}
QString GetCover::get_thumb_name(const QString& hstr)
{
    QString res = QString("/tmp/") + hstr + QString(".png");
    return res;
}
QString GetCover::md5sum(const char* buffer, int size)
{
    QCryptographicHash hash( QCryptographicHash::Md5 );
    hash.addData(buffer, size);
    QString str_hash = hash.result().toHex().data();
    return str_hash;
}

QString GetCover::get_hash_filename(const QString& fn)
{
    QCryptographicHash hash( QCryptographicHash::Md5 );
    hash.addData(fn.toStdString().c_str(), fn.length());
    QString str_hash = hash.result().toHex().data();
    return str_hash;
}

bool GetCover::getcover(const QString& fn, QString& tbfn)
{
    QFile fileobj(fn);
    //fileobj.setFileName(tbfn);
    if (!fileobj.exists()) {
        qDebug() << fn << "not exists";
        return false;
    }

    QRegExp rxmp3("\\.mp3$");
    QRegExp rxm4a("\\.m4a$");
    bool ret = false;

    if (fn.contains(rxmp3)) {
        //qDebug() << "call extract_cover_from_mp3()...";
        ret = extract_cover_from_mp3(fn, tbfn);
    } else if (fn.contains(rxm4a)) {
        //qDebug() << "call extract_cover_from_mp4()...";
        ret = extract_cover_from_mp4(fn, tbfn);
    }

    return ret;
}

bool GetCover::extract_cover_from_mp3(const QString& fn, QString& tbfn)
{
    TagLib::MPEG::File file(fn.toStdString().c_str());
    tbfn = "";
    if (!file.isValid()) {
        //qDebug() << "file is invalid";
        return false;
    }
    if (!file.hasID3v2Tag()) {
        return false;
    }

    //qDebug() << "id3v2 tag...";
    TagLib::ID3v2::Tag *tag = file.ID3v2Tag();
    // m_artist = tag->artist().toCString(true);
    // m_album = tag->album().toCString(true);
    // m_title = tag->title().toCString(true);
    TagLib::ID3v2::FrameList frames = tag->frameListMap()["APIC"];
    if (frames.isEmpty()) {
        //qDebug() << "APIC frame is empty";
        return false;
    }
/*
      ID3v2::FrameList::ConstIterator it = id3v2tag->frameList().begin();
      for(; it != id3v2tag->frameList().end(); it++)
        cout << (*it)->frameID() << " - \"" << (*it)->toString() << "\"" << endl;
*/
    TagLib::ID3v2::FrameList::ConstIterator it = frames.begin();
    //cout << (*it)->frameID() << "==>" << (*it)->toString();
    QString tbtype = (*it)->toString().toCString(); // shows: APIC
    qDebug() << (*it)->frameID().data() << "type:" << tbtype;   // shows: images/jpeg
    //cast Frame * to AttachedPictureFrame*
    TagLib::ID3v2::AttachedPictureFrame *pf = static_cast<TagLib::ID3v2::AttachedPictureFrame *> (*it);
    if (pf == NULL) {
        //qDebug() << "getMP3Frame: pf is null";
        return false;
    }
    bool isJpeg = tbtype.contains("jpeg");
    /// _img is the original thumbnail from media file
    QImage _img;
    _img.loadFromData((const uchar*)pf->picture().data(), pf->picture().size());
    bool ret = save_thumbnail(_img, tbfn, isJpeg);

    return ret;
}

/**
    \return true if thumbnail extracted, false if no thumbnail
**/
bool GetCover::extract_cover_from_mp4(const QString& fn, QString& tbfn)
{
    TagLib::MP4::File file(fn.toStdString().c_str());
    TagLib::MP4::Tag *tag = file.tag();
    tbfn = "";
    if (tag == NULL) {
        //qDebug() << "tag is null";
        return false;
    }
    // m_artist = tag->artist().toCString(true);
    // m_album = tag->album().toCString(true);
    // m_title = tag->title().toCString(true);
    /// get covr from m4a
    if ( !tag->itemListMap().contains("covr") ) {
        //qDebug() << "no covr";
        return false;
    }

    //qDebug() << "get covr...";
    TagLib::MP4::CoverArtList list = tag->itemListMap()["covr"].toCoverArtList();
    // const char *psz_format = list[0].format() == TagLib::MP4::CoverArt::PNG ? "image/png" : "image/jpeg";
    // (void)psz_format;
    bool isJpeg = (list[0].format() == TagLib::MP4::CoverArt::JPEG);
//    qDebug() << "id3tag: mp4: found embedded art: " << psz_format << ", "
//             << list[0].data().size() << "bytes";
    QImage _img;
    _img.loadFromData((const uchar *)list[0].data().data(), list[0].data().size());
    //QString confmd5 = ();

    bool ret = save_thumbnail(_img, tbfn, isJpeg);
    return ret;
}

bool GetCover::save_thumbnail(const QImage& img, QString& tbfn, bool isJpeg)
{
    QString hstr = md5sum((const char*)img.constBits(), img.byteCount());
    //qDebug() << "hstr:" << hstr;
    tbfn = get_thumb_name(hstr);
    //qDebug() << "tbfn:" << hstr;
    if ( isFileExisted(tbfn) ) {
        //qDebug() << "such thumbnail existed, don't save and report last tbfn:" << tbfn;
        return true;
    }

    const int DEFAULT_SHRINK_WIDTH = 800;
    const int DEFAULT_SHRINK_HEIGHT = 800;
    if (m_writetb) {
        // m_resizetb will ignore m_followtype
        if (m_resizetb) {
            QImage resized_img = img.scaled(
                QSize(DEFAULT_SHRINK_WIDTH, DEFAULT_SHRINK_HEIGHT),
                Qt::KeepAspectRatio);
            resized_img.save(tbfn, "PNG");
        } else {
            if (m_followtype && isJpeg) {
                    img.save(tbfn, "JPG");
            } else {
                img.save(tbfn, "PNG");
            }
        }
    } else {
        qDebug() << "will not save tb...";
    }

    //qDebug() << "thumbnail:" << tbfn;
    return true;
}

bool GetCover::isFileExisted(const QString& fn)
{
    QFile fileobj(fn);
    return fileobj.exists();
}

void GetCover::setWriteTb(bool b)
{
    m_writetb = b;
}
void GetCover::setFollowImageType(bool b)
{
    m_followtype = b;
}
void GetCover::setResizeTb(bool b)
{
    m_resizetb = b;
}
void GetCover::show_toggles()
{
    qDebug() << "m_writetb" << (m_writetb?"on":"off")
        << "m_followtype" << (m_followtype?"on":"off")
        << "m_resizetb" << (m_resizetb?"on":"off");
}
