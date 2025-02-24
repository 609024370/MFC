/********************************************************************
    File:	        CompareTaskRuns	
    Creation Date:	2009/11/01
	
	Author: 	    Ahmed Charfeddine
					info@potatosoftware.com

	License:        Copyright [2009] [Potato software]

					Licensed under the Apache License, Version 2.0 (the "License");
					you may not use this file except in compliance with the License.
					You may obtain a copy of the License at

							http://www.apache.org/licenses/LICENSE-2.0

					Unless required by applicable law or agreed to in writing, software
					distributed under the License is distributed on an "AS IS" BASIS,
					WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
					See the License for the specific language governing permissions and
					limitations under the License.
    
	Note :	  		
*********************************************************************/
#pragma once
#include "comparetool.h"

class CCompareTaskRuns :
	public CCompareTool
{
public:
	CCompareTaskRuns(void);
	~CCompareTaskRuns(void);
	virtual void execute(std::vector<CTest*> tests,std::string targetName,std::string extraTargetName);
	virtual void render()
	{
		//
	}
};
