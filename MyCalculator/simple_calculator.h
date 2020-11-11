/// MyCalculator.h: главный файл заголовка для приложения PROJECT_NAME
///

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		/// основные символы


/// CMyCalculatorApp:
/// Сведения о реализации этого класса: MyCalculator.cpp
///

class CMyCalculatorApp : public CWinApp
{
public:
	CMyCalculatorApp();

/// Переопределение
public:
	virtual BOOL InitInstance();

/// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMyCalculatorApp theApp;
