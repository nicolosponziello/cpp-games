#ifndef ANIMATION
#define ANIMATION

enum AnimationTypes
{
    ONE,
    TWO,
    THREE
};

class Animation
{
public:
    Animation(int start, int end)
    {
        mStart = start;
        mEnd = end;
    }
    int GetStartIndex() const { return mStart; }
    int GetEndIndex() const { return mEnd; }

private:
    int mStart;
    int mEnd;
};

#endif