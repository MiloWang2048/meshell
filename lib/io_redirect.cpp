#include "meshell.h"

MeshStatus handle_redirect(Args& args, RedirectParams& params) {
  auto inFlagPos = find(args.begin(), args.end(), "<");
  auto outFlagPos = find(args.begin(), args.end(), ">");

  if (inFlagPos != args.end()) {
    if (inFlagPos == (args.end() - 1)) {
      cout << "no file to read. abort." << endl;
      return RETURN_FAIL;
    }
    ifstream* inFile = new ifstream(*(inFlagPos + 1));
    if ((*inFile).fail()) {
      cout << "fail to read file. abort." << endl;
      return RETURN_FAIL;
    }
    params.infile = inFile;
    params.stdinBackup = cin.rdbuf();
    cin.rdbuf((*inFile).rdbuf());
    args.erase(inFlagPos);
    args.erase(inFlagPos);
  } else {
    params.infile = NULL;
  }

  if (outFlagPos != args.end()) {
    if (outFlagPos == (args.end() - 1)) {
      cout << "no file to read. abort." << endl;
      return RETURN_FAIL;
    }
    ofstream* outFile = new ofstream(*(outFlagPos + 1));
    if ((*outFile).fail()) {
      cout << "fail to read file. abort." << endl;
      return RETURN_FAIL;
    }
    params.outfile = outFile;
    params.stdoutBackup = cout.rdbuf();
    cout.rdbuf((*outFile).rdbuf());
    args.erase(outFlagPos);
    args.erase(outFlagPos);
  } else {
    params.outfile = NULL;
  }
  return SIGNAL_EXIT;
}

void restore_std_stream(RedirectParams& params) {
  if (params.infile) {
    cin.rdbuf(params.stdinBackup);
    params.infile->close();
  }
  if (params.outfile) {
    cout.rdbuf(params.stdoutBackup);
    params.outfile->close();
  }
}