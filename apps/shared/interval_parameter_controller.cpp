#include "interval_parameter_controller.h"
#include <assert.h>

namespace Shared {

IntervalParameterController::IntervalParameterController(Responder * parentResponder, Interval * interval) :
  FloatParameterController(parentResponder),
  m_interval(interval),
  m_intervalStartCell(PointerTableCellWithEditableText(&m_selectableTableView, this, m_draftTextBuffer, (char*)"X Debut")),
  m_intervalEndCell(PointerTableCellWithEditableText(&m_selectableTableView, this, m_draftTextBuffer, (char*)"X Fin")),
  m_intervalStepCell(PointerTableCellWithEditableText(&m_selectableTableView, this, m_draftTextBuffer, (char*)"Pas"))
{
}

const char * IntervalParameterController::title() const {
  return "Regler l'intervalle";
}

Interval * IntervalParameterController::interval() {
  return m_interval;
}

float IntervalParameterController::parameterAtIndex(int index) {
  GetterPointer getters[k_totalNumberOfCell] = {&Interval::start, &Interval::end, &Interval::step};
  return (m_interval->*getters[index])();
}

void IntervalParameterController::setParameterAtIndex(int parameterIndex, float f) {
  SetterPointer setters[k_totalNumberOfCell] = {&Interval::setStart, &Interval::setEnd, &Interval::setStep};
  (m_interval->*setters[parameterIndex])(f);
}

int IntervalParameterController::numberOfRows() {
  return k_totalNumberOfCell;
};

HighlightCell * IntervalParameterController::reusableCell(int index) {
  assert(index >= 0);
  assert(index < k_totalNumberOfCell);
  HighlightCell * cells[] = {&m_intervalStartCell, &m_intervalEndCell, &m_intervalStepCell};
  return cells[index];
}

int IntervalParameterController::reusableCellCount() {
  return k_totalNumberOfCell;
}

}