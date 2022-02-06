## Fix submodule stale/inconsistent sha issues
```
git pull --prune --recurse-submodules --force

Another approach is to
rm -rf path/to/submodule
git checkout path/to/submodule
```
