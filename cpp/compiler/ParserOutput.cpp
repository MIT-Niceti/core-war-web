#include "ParserOutput.hh"
#include "AOutput.hh"
#include <iostream>

ParserOutput::ParserOutput()
{
}

ParserOutput::~ParserOutput()
{
}

void ParserOutput::addElement(const Token *token, unsigned int i)
{
    while (_input.size() > i)
    {
        delete _input.back();
        _input.pop_back();
    }

    _input.push_back(new element(token, i));
}

void ParserOutput::constructOutput(const std::string &ruleName, unsigned int iStart, unsigned int iEnd)
{
    eType ruleType = _getRuleTypeFromRuleName(ruleName);

    --iEnd;
    if (ruleType != eType::INVALID)
    {
        std::vector<element *> *ruleElemsOutput = new std::vector<element *>;

        // std::cout << "Found valid rule '" << ruleName << "'"
        //     << " | type = " << ruleType
        //     << " | indexStart = " << iStart
        //     << " | indexEnd = " << iEnd
        //     << " | _input.size() = " << _input.size() << std::endl;
        for (element *ruleElem : _input)
        {
            if (ruleElem->i >= iStart && ruleElem->i <= iEnd)
            {
                ruleElem->type = ruleType;
                ruleElemsOutput->push_back(ruleElem);
            }
        }

        auto rIt = _output.rbegin();
        while (rIt != _output.rend())
        {
            AOutput *elem = *rIt;

            ++rIt;
            // std::cout << "Elem: " << elem->type() << " | elem->iStart() = " << elem->iStart() << " | elem->iEnd() = " << elem->iEnd() << std::endl;
            if (elem->iStart() == iStart && elem->iEnd() == iEnd)
            {
                delete elem;
                _output.pop_back();
            }
        }

        _output.push_back(_createRuleOutput(ruleType, ruleElemsOutput));
        // std::cout << "Pushed elem: " << ruleOutput->type() << " | ruleOutput->iStart() = " << ruleOutput->iStart() << " | ruleOutput->iEnd() = " << ruleOutput->iEnd() << std::endl;
    }
}

AOutput *ParserOutput::_createRuleOutput(eType ruleType, std::vector<element *> *elements)
{
    AOutput *ruleOutput = NULL;

    if (ruleType == ParserOutput::eType::META_NAME)
        ruleOutput = new AOutput::MetaName(ruleType, elements);
    else if (ruleType == ParserOutput::eType::META_COMMENT)
        ruleOutput = new AOutput::MetaComment(ruleType, elements);
    else if (ruleType == ParserOutput::eType::INSTRUCTION)
        ruleOutput = new AOutput::Instruction(ruleType, elements);
    else if (ruleType == ParserOutput::eType::LABEL)
        ruleOutput = new AOutput::Label(ruleType, elements);
    else if (ruleType == ParserOutput::eType::INSTRUCTION_AND_LABEL)
        ruleOutput = new AOutput::InstructionAndLabel(ruleType, elements);
    else if (ruleType == ParserOutput::eType::INSTRUCTION_NAME)
        ruleOutput = new AOutput::InstructionName(ruleType, elements);
    else if (ruleType == ParserOutput::eType::REGISTER_PARAMETER)
        ruleOutput = new AOutput::ParameterRegister(ruleType, elements);
    else if (ruleType == ParserOutput::eType::DIRECT_PARAMETER)
        ruleOutput = new AOutput::ParameterDirect(ruleType, elements);
    else if (ruleType == ParserOutput::eType::INDIRECT_PARAMETER)
        ruleOutput = new AOutput::ParameterIndirect(ruleType, elements);
    return ruleOutput;
}

AOutput *ParserOutput::finalizeOutput()
{
    auto rIt = _output.rbegin();

    // std::cout << "There is " << _output.size() << " element(s)" << std::endl;
    // while (rIt != _output.rend())
    // {
    //     (*rIt)->print();
    //     ++rIt;
    // }

    // Hmm its dirty
    rIt = _output.rbegin();
    AOutput *prev = NULL;
    while (rIt != _output.rend())
    {
        (*rIt)->setPrev(prev);
        prev = *rIt;
        ++rIt;
    }

    auto it = _output.begin();
    AOutput *next = NULL;
    while (it != _output.end())
    {
        (*it)->setNext(next);
        next = *it;
        ++it;
    }

    if (!_output.empty())
    {
        if (_output.back()->type() == ParserOutput::eType::META_NAME)
            static_cast<AOutput::MetaName *>(_output.back())->metamorhose();
        else if (_output.back()->type() == ParserOutput::eType::META_COMMENT)
            static_cast<AOutput::MetaComment *>(_output.back())->metamorhose();
        else if (_output.back()->type() == ParserOutput::eType::INSTRUCTION)
            static_cast<AOutput::Instruction *>(_output.back())->metamorhose();
        else if (_output.back()->type() == ParserOutput::eType::LABEL)
            static_cast<AOutput::Label *>(_output.back())->metamorhose();
        else if (_output.back()->type() == ParserOutput::eType::INSTRUCTION_AND_LABEL)
            static_cast<AOutput::InstructionAndLabel *>(_output.back())->metamorhose();
        else if (_output.back()->type() == ParserOutput::eType::INSTRUCTION_NAME)
            static_cast<AOutput::InstructionName *>(_output.back())->metamorhose();
        else if (_output.back()->type() == ParserOutput::eType::REGISTER_PARAMETER)
            static_cast<AOutput::ParameterRegister *>(_output.back())->metamorhose();
        else if (_output.back()->type() == ParserOutput::eType::DIRECT_PARAMETER)
            static_cast<AOutput::ParameterDirect *>(_output.back())->metamorhose();
        else if (_output.back()->type() == ParserOutput::eType::INDIRECT_PARAMETER)
            static_cast<AOutput::ParameterIndirect *>(_output.back())->metamorhose();
        return _output.back();
    }
    return NULL;
}

ParserOutput::eType ParserOutput::_getRuleTypeFromRuleName(const std::string &ruleName) const
{
    if (ruleName == "metaNameDeclaration")
        return eType::META_NAME;
    else if (ruleName == "metaCommentDeclaration")
        return eType::META_COMMENT;
    else if (ruleName == "labelAndInstructionDeclaration")
        return eType::INSTRUCTION_AND_LABEL;
    else if (ruleName == "instructionDeclaration")
        return eType::INSTRUCTION;
    else if (ruleName == "labelDeclaration")
        return eType::LABEL;
    else if (ruleName == "indirectValueParameter")
        return eType::INDIRECT_PARAMETER;
    else if (ruleName == "instructionName")
        return eType::INSTRUCTION_NAME;
    else if (ruleName == "registerParameter")
        return eType::REGISTER_PARAMETER;
    else if (ruleName == "directValueParameter")
        return eType::DIRECT_PARAMETER;
    else if (ruleName == "indirectValueParameter")
        return eType::INDIRECT_PARAMETER;
    return eType::INVALID;
}
