#include "Translator.hh"
#include "ParserOutput.hh"
#include <iostream>
#include <fstream>

Translator::Translator()
{
}

Translator::~Translator()
{
}

bool Translator::translate(ParsedLines *parserOutput)
{
    return _fillOutputStructure(parserOutput) &&
        _translated.sortLabelsAndInstructions() &&
        _translated.computeLabelValues() &&
        _translated.computeProgramSize();
}

bool Translator::write(const std::string &fileName)
{
    std::ofstream file;

    file.open(fileName, std::ios::binary | std::ios::trunc);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open output file '" << fileName << "'" << std::endl;
        return false;
    }
    return _translated.write(file);
}

bool Translator::_fillOutputStructure(ParsedLines *parserOutput)
{
    for (AOutput *line : *parserOutput)
    {
        if (line->type() == ParserOutput::META_NAME)
        {
            if (!_translated.translateMetaName(static_cast<AOutput::MetaName *>(line)))
                return false;
        }
        else if (line->type() == ParserOutput::META_COMMENT)
        {
            if (!_translated.translateMetaComment(static_cast<AOutput::MetaComment *>(line)))
                return false;
        }
        else if (line->type() == ParserOutput::LABEL)
        {
            if (!_translated.translateLabel(static_cast<AOutput::Label *>(line)))
                return false;
        }
        else if (line->type() == ParserOutput::INSTRUCTION)
        {
            if (!_translated.translateInstruction(static_cast<AOutput::Instruction *>(line)))
                return false;
        }
        else if (line->type() == ParserOutput::INSTRUCTION_AND_LABEL)
        {
            if (!_translated.translateInstructionAndLabel(static_cast<AOutput::InstructionAndLabel *>(line)))
                return false;
        }
        else
        {
            std::cerr << "Unknown error in translator" << std::endl;
            return false;
        }
    }
    return true;
}
