#ifndef ANIMATION
#define ANIMATION

class Animation
{
public:
    Animation(int start, int end, bool looping)
    {
        mStart = start;
        mEnd = end;
        mLooping = looping;
    }
    int GetStartIndex() const { return mStart; }
    int GetEndIndex() const { return mEnd; }
    bool IsLooping() const { return mLooping; }

private:
    int mStart;
    int mEnd;
    bool mLooping;
};

#endif