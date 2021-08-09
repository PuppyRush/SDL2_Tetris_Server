#pragma once
#ifndef EASYTIMER_ELAPSEDTIMER_H
#define EASYTIMER_ELAPSEDTIMER_H


#if _MSC_VER >= 1200
#pragma once
#endif

#include "TimerBasic.h"

namespace easytimer {

template <typename _Rep, typename _Rn = long long>
class ElapsedTimer : public TimerBasic<_Rep, _Rn>
{
public:

	ElapsedTimer() = default;
	virtual ~ElapsedTimer() = default;

};

}


#endif
