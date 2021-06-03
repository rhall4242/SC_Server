/*
  ==============================================================================

    TestNode.cpp
    Created: 3 Jun 2021 2:41:20pm
    Author:  rhall

  ==============================================================================
*/

#include  "../Node.h"
#include "CppUnitTestFramework.hpp"

struct NodeTestFixture 
{ 
  MonoAudioInputConnector inp {"Input"};
  MonoAudioOutputConnector out {"Output"};
};

TEST_CASE(NodeTestFixture, Test1) 
{
  Connection c;
  c.connect(&out, &inp);
  CHECK_EQUAL(c.to, &inp);
};

