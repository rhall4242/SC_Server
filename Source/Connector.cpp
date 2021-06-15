/*
  ==============================================================================

    Connector.cpp
    Created: 31 May 2021 9:43:31am
    Author:  rhall

  ==============================================================================
*/

#include "Connector.h"
#include "Node.h"

///
/// Connect to an InputConnection to an OutputConnection
/// @param f - The output connection from which the connection originates
/// @param t - The input connection to which the output is being connected
///

void Connection::connect(OutputConnector* f, InputConnector* t)
{
  from = f;
  to = t;
  from->to.insert(std::make_pair(t->getName(), t));
  from->setConnected(true);
  from->owner->updateConnections();
  to->from = f;
  to->setConnected(true);
  to->owner->updateConnections();
}