#ifndef GAMEFILE_H_INCLUDED
#define GAMEFILE_H_INCLUDED
#define N 14

extern double v[N];
extern void save(const double (&a)[N]);
extern double (&load())[N];
extern bool checkGameFile();

#endif // GAMEFILE_H_INCLUDED
