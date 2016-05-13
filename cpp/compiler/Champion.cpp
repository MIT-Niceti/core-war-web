#include "Champion.hh"
#include "ChampionHeader.hh"
#include "ChampionInstruction.hh"
#include "ChampionInstructionParameter.hh"
#include <cstddef>
#include <iostream>

Champion::Champion()
    : _header(NULL)
{
}

Champion::~Champion()
{
}

bool Champion::translateMetaName(AOutput::MetaName *input)
{
    _initHeader();
    return _header->setName(input);
}

bool Champion::translateMetaComment(AOutput::MetaComment *input)
{
    _initHeader();
    return _header->setComment(input);
}

bool Champion::translateLabel(AOutput::Label *input)
{
    Label *label = new Label;

    if (!(label->translate(input)))
    {
        delete label;
        return false;
    }
    _instructions.push_back(label);
    _labels.push_back(label);
    return true;
}

bool Champion::translateInstruction(AOutput::Instruction *input)
{
    Instruction *instruction = new Instruction;

    if (!(instruction->translate(input)))
    {
        delete instruction;
        return false;
    }
    _instructions.push_back(instruction);
    return true;
}

bool Champion::translateInstructionAndLabel(AOutput::InstructionAndLabel *input)
{
    return translateLabel(input->label()) && translateInstruction(input->instruction());
}

bool Champion::sortLabelsAndInstructions()
{
    std::vector<Instruction *> reArrangedInstructions;
    std::vector<Instruction *> reArrangedLabels;

    for (unsigned int i = 0; i != _instructions.size(); ++i)
    {
        Instruction *instruction = _instructions[i];

        if (instruction->hasLabel() && !instruction->hasOpCode())
        {
            if (i + 1 < _instructions.size() && !_instructions[i + 1]->hasLabel())
            {
                instruction->setOpCode(_instructions[i + 1]->opCode());
                ++i;
            }
            else
            {
                std::cerr << "Error: Label '" << instruction->labelName() << "' points to no instruction" << std::endl;
                return false;
            }
        }
        reArrangedInstructions.push_back(instruction);

        if (instruction->hasLabel())
            reArrangedLabels.push_back(instruction);
    }
    _instructions = reArrangedInstructions;
    _labels = reArrangedLabels;
    return _checkMultipleLabelDefinition();
}

bool Champion::computeLabelValues()
{
    for (int i = 0; i != (int)_instructions.size(); ++i)
    {
        Instruction *instruction = _instructions[i];

        for (Instruction::Parameter *parameter : instruction->parameters())
        {
            if (parameter->isLabel())
            {
                for (int j = 0; j != (int)_instructions.size(); ++j)
                {
                    if (_instructions[j]->hasLabel() && parameter->label() == _instructions[j]->labelName())
                    {
                        if (parameter->type() == Instruction::Parameter::DIRECT)
                            parameter->setDirectValue(_computeLabelJump(i, j));
                        else if (parameter->type() == Instruction::Parameter::INDIRECT)
                            parameter->setIndirectValue(_computeLabelJump(i, j));
                        break ;
                    }
                }
            }
        }
    }
    return true;
}

int Champion::_computeLabelJump(int i, int j)
{
    int start = i <= j ? i : j;
    int end = i <= j ? j : i;
    int bytesJump = 0;

    while (start != end)
    {
        bytesJump += _instructions[start]->size();
        ++start;
    }
    return i > j ? bytesJump * -1 : bytesJump;
}

bool Champion::_checkMultipleLabelDefinition()
{
    for (unsigned int i = 0; i != _labels.size(); ++i)
    {
        for (unsigned int j = 0; j != _labels.size(); ++j)
        {
            if (i != j && _labels[i]->labelName() == _labels[j]->labelName())
            {
                std::cerr << "Error: Multiple declaration of label '" << _labels[i]->labelName() << "'" << std::endl;
                return false;
            }
        }
    }
    return true;
}

void Champion::_initHeader()
{
    if (!_header)
        _header = new Header();
}
