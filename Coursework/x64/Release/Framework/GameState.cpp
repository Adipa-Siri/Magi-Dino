#include "GameState.h"

// Set the current state
void GameState::setCurrentState(State s)
{
	m_currentState = s;
}

// Returns the current state.
State GameState::getCurrentState()
{
	return m_currentState;
}
void GameState::setPreviousState(State ps) {

	m_previousState = ps;

}

State GameState::getPreviousState() {
	return m_previousState;

}