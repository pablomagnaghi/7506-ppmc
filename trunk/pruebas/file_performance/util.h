#ifndef _util_h_
#define _util_h_

namespace util {
	class FileError:public std::exception {

	};
	
	class FileErrorOpenForReading:public FileError{
		virtual const char* what() const throw() {
			return "FileErrorOpenForReading";
		}
	};
	class FileErrorRead:public FileError{
		virtual const char* what() const throw() {
			return "FileErrorRead";
		}
	};
	class FileErrorOpenForWriting:public FileError{
		virtual const char* what() const throw() {
			return "FileErrorOpenForWriting";
		}
	};
	class FileErrorCharWrite:public FileError{
		virtual const char* what() const throw() {
			return "FileErrorCharWrite";
		}
	};
	class FileErrorStringWrite:public FileError{
		virtual const char* what() const throw() {
			return "FileErrorStringWrite";
		}
	};
	class FileErrorBufferWrite:public FileError{
		virtual const char* what() const throw() {
			return "FileErrorBufferWrite";
		}
	};
}

#endif  // _util_h_