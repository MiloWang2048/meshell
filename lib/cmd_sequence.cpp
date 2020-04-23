#include "meshell.h"

MeshStatus cmd_sequence(MeshConfig* config, Args& args) {
  RedirectParams redirectParams;
  auto failToRedirect = handle_redirect(args, redirectParams);
  if (failToRedirect)
    return failToRedirect;
  CommandStatus stat = built_in_cmds(config, args);
  //puts(stat == CMD_FALLTHROUGH ? "falltrough" : "captured");
  if (stat == CMD_FALLTHROUGH) {
    stat = outer_cmds(config, args);
  }
  restore_std_stream(redirectParams);
  return RETURN_SUCCESS;
}

MeshStatus bg_cmd_sequence(MeshConfig* config, Args& args) {
  args.erase(args.end() - 1);
  pid_t pid = fork();
  if (pid == 0) {
    // child
    MeshStatus stat = cmd_sequence(config, args);
    exit(stat);
  } else if (pid < 0) {
    // error
    puts("error: cannot fork");
    return RETURN_FAIL;
  } else {
    // parent
    return RETURN_SUCCESS;
  }
  return RETURN_SUCCESS;
}