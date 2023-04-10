#include "stdafx.h"
#include "CommentOption.h"


CCommentOption::CCommentOption()
{
	memset(m_enumsymbol, 0, sizeof(m_enumsymbol));
	memset(m_comment, 0, sizeof(m_comment));
}


CCommentOption::~CCommentOption()
{
}
