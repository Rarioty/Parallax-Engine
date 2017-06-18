#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP

namespace Parallax
{
    /**
     * \namespace   Parallax::Core
     * \ingroup     Core
     */
    namespace Core
    {
        /**
         * \namespace   Parallax::Core::Parser
         * \ingroup     Core
         */
        namespace Parser
        {
            /**
             * \class   CSVParser
             * \brief   Parser for CSV file format
             *
             * \ingroup Core
             */
            class CSVParser : public Parser
            {
            public:
                CSVParser();
                ~CSVParser();
            };
        }
    }
}

#endif
