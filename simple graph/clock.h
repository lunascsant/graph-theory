
/************************************************************************************
 * Arquivo     : clock.h                                                            *
 * Dependencias: clock.h, types.h                                                   *
 * Autor       : Eyder Rios (erios@ic.uff.br)                                       *
 * Data        : 17/04/2002                                                         *
 * Descricao   : Implementa rotinas para contagem de tempo, data e hora.            *
 ************************************************************************************/

#ifndef __clock_h__
#define __clock_h__

#include <time.h>

typedef struct tagDATETIME {
          unsigned  short int  dt_year;        // ano: com 4 digitos
          unsigned  short int  dt_month;       // mes: 1-12
          unsigned  short int  dt_day;         // dia: 1-31
          unsigned  short int  dt_wday;        // dia da semana: 0-6 (0=domingo - 6=sabado)
          unsigned  short int  dt_yday;        // dia do ano: 1-365
          unsigned  short int  dt_hour;        // hora: 0-23
          unsigned  short int  dt_min;         // minuto: 0-59
          unsigned  short int  dt_sec;         // segundo: 0-59
        } DATETIME, *PDATETIME;

// identificador do contador de tempo
typedef unsigned long int   TIMER, *PTIMER;

typedef struct tagCOMPTIME {
          TIMER   t_timer;
          unsigned long int   t_min;
          unsigned long int   t_max;
          unsigned  short int    t_upt;
          float    t_sum;
          float    t_avg;
        } COMPTIME, *PCOMPTIME;

unsigned long int  timer_tick  ();
unsigned long int  timer_wait  (unsigned long int time);

unsigned long int  timer_start    (PTIMER timer);
unsigned long int  timer_enlapsed (PTIMER timer);

void   clock_datetime (PDATETIME dt);
void   clock_fdate    (PDATETIME dt, char *str_date);
void   clock_ftime    (PDATETIME dt, char *str_time);
void   clock_fdatetime(PDATETIME dt, char *str);

void   comptime_start  (PCOMPTIME ctime);
void   comptime_update (PCOMPTIME ctime);

#endif
