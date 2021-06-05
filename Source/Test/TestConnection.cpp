/*
  ==============================================================================

    TestConnection.cpp
    Created: 2 Jun 2021 9:28:56pm
    Author:  rhall

  ==============================================================================
*/
#include "../MidiInputNode.h"
#include  "../Connector.h"
#include "CppUnitTestFramework.hpp"

struct ConnectionTestFixture 
{ 
  MonoAudioInputConnector inp {"Input"};
  MonoAudioOutputConnector out {"Output"};
};

TEST_CASE(ConnectionTestFixture, Test1) 
{
  Connection c;
  c.connect(&out, &inp);
  CHECK_EQUAL(c.to, &inp);
};

TEST_CASE(ConnectionTestFixture, Test2) 
{
  Connection c;
  c.connect(&out, &inp);
  CHECK_EQUAL(out.to["Input"], &inp);
};

TEST_CASE(ConnectionTestFixture, Test3) 
{
  Connection c;
  c.connect(&out, &inp);
  CHECK_TRUE(c.to->isConnected());
};

TEST_CASE(ConnectionTestFixture, Test4) 
{
  Connection c;
  c.connect(&out, &inp);
  CHECK_TRUE(c.from->isConnected());
};

int testmain(int argc, const char* argv[]) {
    CppUnitTestFramework::RunOptions options;
    if (!options.ParseCommandLine(argc, argv)) {
        return 2;
    }

    bool success = CppUnitTestFramework::TestRegistry::Run(
        &options,
        CppUnitTestFramework::ConsoleLogger::Create(&options)
    );

    return success ? 0 : 1;
}

struct NodeTestFixture 
{ 
  MonoAudioInputConnector inp {"Input"};
  MonoAudioOutputConnector out {"Output"};
  MidiInputNode testNode {"TestNode"};
};

TEST_CASE(NodeTestFixture, Test5) 
{
  Connection c;
  c.connect(&out, &inp);
  CHECK_EQUAL(c.to, &inp);
};

