/* FILE NAME   : timer.h
 * PROGRAMMER  : TT6
 * LAST UPDATE : 26.08.2021
 * PURPOSE     : Timer implementation module.
 */

#ifndef __timer_h
#define __timer_h

#include "def.h"

/* Project namespace */
namespace tart
{
  /* Time handle class */
  class timer
  {
  private:
    /* Timer data */
    UINT64
      StartTime,    /* Start program time */
      OldTime,      /* Previous frame time */
      OldTimeFPS,   /* Old time FPS measurement */
      PauseTime,    /* Time during pause period */
      TimePerSec,   /* Timer resolution */
      FrameCounter; /* Frames counter */

  public:
    /* time handle */
    DBL
      GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
      Time, DeltaTime,             /* Time with pause and interframe interval */
      FPS;                         /* Frame per second */
    BOOL IsPause;                  /* Pause flag */

    /* Timer initializing function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    timer( VOID ) :
      FrameCounter(0), GlobalTime(0), GlobalDeltaTime(0), Time(0), DeltaTime(0), 
      PauseTime(0), FPS(59.30), IsPause(FALSE)
    {
      LARGE_INTEGER t;

      QueryPerformanceFrequency(&t);
      TimePerSec = t.QuadPart;
      QueryPerformanceCounter(&t);
      StartTime = OldTime = OldTimeFPS = t.QuadPart;
      FrameCounter = 0;
      IsPause = FALSE;
      FPS = 30.0;
      PauseTime = 0;
    } /* End of 'timer' function */

    /* Timer interframe response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      LARGE_INTEGER t;
      timer Anim;

      QueryPerformanceCounter(&t);
      /* Global time */
      GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
      GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
      /* Time with pause */
      if (Anim.IsPause)
      {
        Anim.DeltaTime = 0;
        PauseTime += t.QuadPart - OldTime;
      }
      else
      {
        DeltaTime = Anim.GlobalDeltaTime;
        Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
      }
      /* FPS */
      FrameCounter++;
      if (t.QuadPart - OldTimeFPS > TimePerSec)
      {
        FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
        OldTimeFPS = t.QuadPart;
        FrameCounter = 0;
      }
      OldTime = t.QuadPart;
    } /* End of 'Response' function */
  }; /* End of 'timer' class */
} /* End of 'tart' namespace */

#endif /* __timer_h_ */

/* END OF 'timer.h' FILE */
