#include "qspotifyqueuetracklist.h"

#include <QtCore/QTime>

#include <QtCore/QDebug>

void QSpotifyQueueTrackList::setShuffle(bool s)
{
    if (s == isShuffle()) return;



   QSpotifyTrackList::setShuffle(s);
   if (s) {
       // Fisher Yates algo
       //    To shuffle an array a of n elements (indices 0..n-1):
       //      for i from n − 1 downto 1 do
       //           j ← random integer with 0 ≤ j ≤ i
       //           exchange a[j] and a[i]
       qsrand(QTime::currentTime().msec());

       int size = count();
       m_originalIndexes = QVector<int>(size);
       for (int i = 0; i < size; ++i)
           m_originalIndexes[i] = i;

              // FIXME
       int currIndex = currentPlayIndex() + 1;
       for (int i = size - 1; i > currIndex; --i) {
           int  j = qrand() % (i + 1 - currIndex) + currIndex;
           this->swap(i, j);
           if (i != j) {
               m_originalIndexes.replace(i, j);
               m_originalIndexes.replace(j, i);
           }
       }
       qDebug() << m_originalIndexes;
   } else {
       // FIXME
   }
//    -
//    -    m_shuffleList.clear();
//    -    m_shuffleIndex = 0;
//    -    bool currentTrackStillExists = m_currentTrack && contains(m_currentTrack);
//    -
//    -    if (m_shuffle) {
//    -
//    -        int currentTrackIndex = 0;
//    -        if (currentTrackStillExists) {
//    -            currentTrackIndex = indexOf(m_currentTrack);
//    -            m_shuffleList.append(currentTrackIndex);
//    -        }
//    -        QList<int> indexes;
//    -        for (int i = 0; i < count(); ++i) {
//    -            if ((currentTrackStillExists && i == currentTrackIndex) || !at(i)->isAvailable())
//    -                continue;
//    -            indexes.append(i);
//    -        }
//    -        while (!indexes.isEmpty()) {
//    -            int i = indexes.takeAt(indexes.count() == 1 ? 0 : (qrand() % (indexes.count() - 1)));
//    -            m_shuffleList.append(i);
//    -        }
//    -    }
//    -}
}

void QSpotifyQueueTrackList::addTrack(std::shared_ptr<QSpotifyTrack> track)
{
    // FIXME
    Q_UNUSED(track);
}

void QSpotifyQueueTrackList::enqueueTrack(std::shared_ptr<QSpotifyTrack> track)
{
    int insertIndex = m_explicitTracks.size();
    if(!isEmpty() && at(0)->isCurrentPlayingTrack()
            && at(0) != m_explicitTracks.first()) {
        ++insertIndex;
    }
    m_explicitTracks.append(track);
    insertRow(insertIndex, track);
}

void QSpotifyQueueTrackList::enqueueTracks(QSpotifyTrackList *list)
{
    if (list) {
        int insertIndex = m_explicitTracks.size();
        if(!isEmpty() && at(0)->isCurrentPlayingTrack()
                && at(0) != m_explicitTracks.first()) {
            ++insertIndex;
        }
        int size = list->count();
        for (int i = 0; i < size; ++i) {
            insertRow(insertIndex++, list->at(i));
            m_explicitTracks.append(list->at(i));
        }
    }
}

bool QSpotifyQueueTrackList::isExplicitTrack(const int index) const
{
    if (!isEmpty() && index >= 0 && index < count()) {
        if (index > 0 && index < m_explicitTracks.size())
            return true;
        if (index == 0 && at(0)->isCurrentPlayingTrack()
                && at(0) == m_explicitTracks.first()) {
            return true;
        }
    }
    return false;
}

void QSpotifyQueueTrackList::swap(int index1, int index2)
{
    qDebug() << "QSpotifyQueueTrackList::swap(" << index1 << " " << index2;
    if (index1 == index2) return;
    if (index1 >= 0 && index1 < count() && index2 >= 0 && index2 < count()) {
        beginMoveRows(QModelIndex(), index1, index1, QModelIndex(), index2);
        auto temp = at(index1);
        replace(index1, at(index2));
        replace(index2, temp);
        endMoveRows();
    }
}
