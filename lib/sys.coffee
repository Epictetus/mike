# - sys.js -
#
# Module contains basic functions for interaction with system.

sys = {}

# Native functions

sys.pwd = $mike.System.pwd
sys.cwd = $mike.System.cwd
sys.system = $mike.System.system
sys.exec = $mike.System.system
sys.stdout = $mike.Stdout
sys.stderr = $mike.Stderr

return sys
