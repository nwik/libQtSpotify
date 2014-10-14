#ifndef QSPOTIFYQUEUETRACKLIST_H
#define QSPOTIFYQUEUETRACKLIST_H

#include <QtCore/QQueue>

#include "qspotifytracklist.h"

class QSpotifyQueueTrackList : public QSpotifyTrackList
{
public:
    QSpotifyQueueTrackList(QObject *parent = nullptr)
        : QSpotifyTrackList(parent) {}

    virtual void setShuffle(bool s);

    void addTrack(std::shared_ptr<QSpotifyTrack> track);

    void enqueueTrack(std::shared_ptr<QSpotifyTrack> track);
    void enqueueTracks(QSpotifyTrackList* list);

    bool isExplicitTrack(const int index) const;

private:
    QQueue<std::shared_ptr<QSpotifyTrack> > m_explicitTracks;
    QVector<int> m_originalIndexes;

    void swap(int index1, int index2);
};

#endif // QSPOTIFYQUEUETRACKLIST_H
