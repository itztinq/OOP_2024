#include<iostream>
#include<cstring>
using namespace std;

class MediaSegment {
protected:
    char title[100];
    char author[100];
    int duration;
    int size;
public:
    MediaSegment (char *title = "", char *author = "", int duration = 0, int size = 0) {
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->duration = duration;
        this->size = size;
    }

    virtual double price() = 0;

};

enum AudioFormat{
    mp3, wav, ogg, flac
};

enum VideoCompression {
    x264, Theora, AV1
};


class AudioRecording : virtual public MediaSegment {
protected:
    AudioFormat format;
    short channels;
public:
    AudioRecording (char *title = "", char *author = "", int duration = 0, int size = 0, int format = 0, short channels = 0)
    : MediaSegment(title, author, duration, size) {
        this->format = (AudioFormat) format;
        this->channels = channels;
    }

    double price() const {
        double product = duration * channels;
        if(format == flac) {
            product *= 1.5;
        }
        return product;
    }

    friend ostream& operator<<(ostream &o, const AudioRecording &a) {
        return o<<a.title<<" - "<<a.author<<" - "<<a.duration<<" - "<<a.size<<" - "<<a.price()<<endl;
    }
};

class VideoRecording : virtual public MediaSegment {
protected:
    int width;
    VideoCompression compression;
public:
    VideoRecording (char *title = "", char *author = "", int duration = 0, int size = 0, int width = 0, int compression = 0)
    : MediaSegment(title, author, duration, size) {
        this->width = width;
        this->compression = (VideoCompression) compression;
    }

    double price() const {
        double price;
        if(width <= 1920) {
            price = 100 * duration;
        }
        else {
            price = 170 * duration;
        }

        if(compression == x264) {
            price *= 1.5;
        } else if(compression == Theora) {
            price *= 0.9;
        }
        return price;
    }

    friend ostream& operator<<(ostream &o, const VideoRecording &v) {
        return o<<v.title<<" - "<<v.author<<" - "<<v.duration<<" - "<<v.size<<" - "<<v.width<<" - "<<v.price()<<endl;
    }
};

class MusicVideo : AudioRecording, public VideoRecording {
private:
    char date[9];
public:
    MusicVideo (char *title = "", char *author = "", int duration = 0, int size = 0, int format = 0,
        short channels = 0, int width = 0, int compression = 0, char *date = "")
    : MediaSegment(title, author, duration, size) {
        this->format = (AudioFormat) format;
        this->channels = channels;
        this->width = width;
        this->compression = (VideoCompression) compression;
        strcpy(this->date, date);
    }

    double price() const {
        double result = AudioRecording::price() + VideoRecording::price();
        char year[5];
        strcpy(year, date+4);
        if(strcmp(year, "2010") > 0) {
            result *= 1.3;
        }
        return result;
    }

    friend ostream& operator<<(ostream &o, const MusicVideo &mv) {
        return o<<mv.title<<" - "<<mv.author<<" - "<<mv.date<<" - "<<mv.duration<<" - "<<mv.price()<<endl;
    }
};

double total_price (MediaSegment **segments, int n) {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        sum += (*segments)[i].price();
    }
    return sum;
}

MusicVideo &cheapest_music_video (MediaSegment **segments) {
    MusicVideo *min = nullptr;
    for(int i = 0; i < 9; i++) {
        MusicVideo *casted = dynamic_cast<MusicVideo *>(segments[i]);
        if(casted != NULL) {
            if(min == nullptr) {
                min = casted;
            } else {
                if(casted->price() < min->price()) {
                    min = casted;
                }
            }
        }
    }
    return *min;
}

int main() {
    // daden main
}