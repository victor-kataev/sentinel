#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <deque>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include "progtest_solver.h"
#include "sample_tester.h"
using namespace std;
#endif /* __PROGTEST__ */ 
class CSentinelHacker
{
  public:
    static bool              SeqSolve                      ( const vector<uint64_t> & fragments,
                                                             CBigInt         & res );
    void                     AddTransmitter                ( ATransmitter      x );
    void                     AddReceiver                   ( AReceiver         x );
    void                     AddFragment                   ( uint64_t          x );
    void                     Start                         ( unsigned          thrCount );
    void                     Stop                          ( void );
};
// TODO: CSentinelHacker implementation goes here
//-------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
int                main                                    ( void )
{
  using namespace std::placeholders;
  for ( const auto & x : g_TestSets )
  { 
    CBigInt res;
    assert ( CSentinelHacker::SeqSolve ( x . m_Fragments, res ) );
    assert ( CBigInt ( x . m_Result ) . CompareTo ( res ) == 0 );
  }
  
  CSentinelHacker test;
  auto            trans = make_shared<CExampleTransmitter> ();
  AReceiver       recv  = make_shared<CExampleReceiver> ( initializer_list<uint64_t> { 0x02230000000c, 0x071e124dabef, 0x02360037680e, 0x071d2f8fe0a1, 0x055500150755 } );
  
  test . AddTransmitter ( trans ); 
  test . AddReceiver ( recv ); 
  test . Start ( 3 );
  
  static initializer_list<uint64_t> t1Data = { 0x071f6b8342ab, 0x0738011f538d, 0x0732000129c3, 0x055e6ecfa0f9, 0x02ffaa027451, 0x02280000010b, 0x02fb0b88bc3e };
  thread t1 ( FragmentSender, bind ( &CSentinelHacker::AddFragment, &test, _1 ), t1Data );
  
  static initializer_list<uint64_t> t2Data = { 0x073700609bbd, 0x055901d61e7b, 0x022a0000032b, 0x016f0000edfb };
  thread t2 ( FragmentSender, bind ( &CSentinelHacker::AddFragment, &test, _1 ), t2Data );
  FragmentSender ( bind ( &CSentinelHacker::AddFragment, &test, _1 ), initializer_list<uint64_t> { 0x017f4cb42a68, 0x02260000000d, 0x072500000025 } );
  t1 . join ();
  t2 . join ();
  test . Stop ();
  assert ( trans -> TotalSent () == 4 );
  assert ( trans -> TotalIncomplete () == 2 );
  return 0;  
}
#endif /* __PROGTEST__ */ 
