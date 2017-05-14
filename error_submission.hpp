/**

Copyright 2017 Mayank Mathur

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#ifndef ERROR_SUBMISSION_ESMP
#define ERROR_SUBMISSION_ESMP

#include <string>
#include <fstream>

namespace esmp
{
	struct error_submission
	{
		bool debug_writer_enabled = false;
		bool debug_write_to_file = false;
		bool error_write_to_file = false;
		void submit_error (std::string err)
		{
			if (error_write_to_file)
			{
				std::ofstream out;
				out.open ("ERROR_REPORT.txt", std::ios_base::app);
				out << "Some critical error has occured in the Ninth Sky Library. See the details below: \n\n";
				out << err << "\n\n";
				out.flush();
			}
			else
			{
				std::cout << "Some critical error has occured in the Ninth Sky Library. See the details below: \n\n" << err;
				std::cout << std::endl;
			}
			return void();
		}
		void debug_write (auto dbug)
		{
			if (debug_writer_enabled)
			{
				if (debug_write_to_file)
				{
					std::ofstream out;
					out.open ("DEBUG_REPORT.txt", std::ios_base::app);
					out << "Debug (Ninth Sky Library): \n\n";
					out << dbug << "\n\n";
					out.flush();
				}
				else
				{
					std::cout << "Debug (Ninth Sky Library): " << dbug << std::endl;
				}
			}
			return void();
		}
	} error_report;
}


#endif
