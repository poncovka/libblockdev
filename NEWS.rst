Libblockdev 2.14
----------------

New minor release of the libblockdev library with important fixes and a few new
features, in particular support for the NTFS file system. See below for details.


**Notable changes**

- fixes

  - Fix BSSize memory leaks

  - Fixes for issues discovered by coverity

  - Support for the 'Legacy boot' GPT flag

- features

  - Added function to get DM device subsystem

  - Support for the NTFS file system

  - pkg-config definitions improvements


**Full list of changes**

Jan Pokorny (1):
- Added function to get DM device subsystem

Kai Lüke (2):
- Add function wrappers for NTFS tools
- Add some test cases for NTFS

Vojtech Trefny (29):
- Skip btrfs subvolume tests with btrfs-progs 4.13.2
- Fix BSSize memory leaks in btrfs and mdraid plugins
- Use system values in KbdTestBcacheStatusTest
- Use libbytesize to parse bcache block size
- blockdev.c.in: Fix unused variables
- fs.c: Fix resource leaks in 'bd_fs_get_fstype'
- fs.c: Check sscanf return value in 'bd_fs_vfat_get_info'
- fs.c: Fix for loop condition in 'bd_fs_get_fstype'
- lvm.c: Fix "use after free" in 'bd_lvm_get_thpool_meta_size'
- mdraid.c: Fix resource leaks
- part.c: Check if file discriptor is >= 0 before closing it
- kbd.c: Fix double free in 'bd_kbd_zram_get_stats'
- exec.c: Fix "use after free" in 'bd_utils_check_util_version'
- crypto.c: Use right key buffer in 'bd_crypto_luks_add_key'
- part.c: Fix possible NULL pointer dereference
- fs.c: Fix "forward null" in 'do_mount' and 'bd_fs_xfs_get_info'
- exec.c: Fix resource leaks in 'bd_utils_exec_and_report_progress'
- kbd.c: Fix potential string overflow in 'bd_kbd_bcache_create'
- part.c: Check if we've found a place to put new logical partitions
- exec.c: Ignore errors from 'g_io_channel_shutdown'
- Ignore some coverity false positive errors
- crypto.c: Fix waiting for enough entropy
- exec.c: Fix error message in 'bd_utils_exec_and_report_progress'
- Fix duplicate 'const' in generated functions
- lvm-dbus.c: Fix multiple "use after free" coverity warnings
- fs.c: Fix multiple "forward NULL" warnings in 'bd_fs_ntfs_get_info'
- dm.c: Check return values of dm_task_set_name/run/get_info functions
- dm.c: Fix uninitialized values in various dm plugin functions
- fs.c: Fix potential NULL pointer dereference

Vratislav Podzimek (3):
- Sync spec with downstream
- Add pkgconfig definitions for the utils library
- Respect the version in the blockdev.pc file

intrigeri (1):
- Support the legacy boot GPT flag


Thanks to all our contributors.

Vratislav Podzimek, 2017-10-31


Libblockdev 2.13
----------------

New minor release of the libblockdev library. Most of the changes are bugfixes
related to building and running tests on the s390 architecture and CentOS 7
aarch64. Other than that a support for checking runtime dependencies (utilities)
on demand and querying available technologies was implemented.


**Notable changes**

- builds

  - various fixes for building on s390

- tests

  - various changes allowing running the test suite on s390

  - various changes allowing running the test suite on CentOS7 aarch64

- features

  - checking for runtime dependencies on demand

  - querying available technologies


**Full list of changes**

Vojtech Trefny (14):
- Allow compiling libblockdev without s390 plugin
- Do not run g_clear_error after setting it
- Fix zFCP LUN max length
- Bypass error proxy in s390 test
- Use "AC_CANONICAL_BUILD" to check architecture instead of "uname"
- Do not include s390utils/vtoc.h in s390 plugin
- Add NEWS.rst file
- Fix source URL in spec file
- Use only one git tag for new releases
- Add new function for setting swap label
- Skip btrfs tests on CentOS 7 aarch64
- Better handle old and new zram sysfs api in tests
- Try harder when waiting for lio device to show up
- Use shorter prefix for tempfiles

Vratislav Podzimek (9):
- Add a function for getting plugin name
- Dynamically check for the required utilities
- Add functions for querying available technologies
- Simplify what WITH_BD_BCACHE changes in the KBD plugin
- Add a basic test for the runtime dependency checking
- Add missing items to particular sections in the documentation
- Assign functions to tech-mode categories
- Add a function for enabling/disabling plugins' init checks
- Fix the rpmlog and shortlog targets

Thanks to all our contributors.

Vratislav Podzimek, 2017-09-29


Libblockdev 2.12
----------------

New minor release of libblockdev library. Most changes in this release are related to
improving our test suite and fixing new issues and bugs.

**Notable changes**

- tests

  - various changes allowing running the test suite on Debian

**Full list of changes**

Kai Lüke (1):

- Wait for resized partition

Vojtech Trefny (20):

- Try to get distribution info from "PrettyName" if "CPEName" isn't available
- Require only plugins that are needed for given test
- Try harder to unmount devices in test cleanup
- Fix redirecting command output to /dev/null in tests
- Skip free region tests on Debian too
- Skip the test for device escrow on Debian too
- Skip zRAM tests on Debian
- Skip dependency checking in mpath tests on Debian
- Fix checking for available locales
- Fix names of backing files in tests
- Skip vgremove tests on 32bit Debian
- Use libmount cache when parsing /proc/mounts
- Use mountpoint for "xfs_info" calls
- Close filesystem before closing the partition during FAT resize
- Stop skipping FAT resize tests on rawhide
- Tests: Move library initialization to setUpClass method
- Add a script for running tests
- Use "run_tests" script for running tests from Makefile
- Fix label check in swap_test
- Own directories /etc/libblockdev and /etc/libblockdev/conf.d

Vratislav Podzimek (6):

- Sync spec with downstream
- Use -ff when creating PVs in FS tests
- Confirm the force when creating PVs in FS tests
- Add some space for the CI status
- Make sure the device is opened for libparted
- New version - 2.12

Thanks to all our contributors.

Vratislav Podzimek, 2017-08-30


Libblockdev 2.11
----------------

New minor release of libblockdev library.

**Notable changes**

- library

  - added option to skip dependecy check during library initialization

**Full list of changes**

Kai Lüke (2):

- Link to GObject even if no plugin is activated
- Allow non-source directory builds

Vojtech Trefny (1):

- Use new libmount function to get (un)mount error message

Vratislav Podzimek (6):

- Update the documentation URL
- Keep most utilities available for tests
- Skip zram tests on Rawhide
- Add a way to disable runtime dependency checks
- Make the KbdZRAMDevicesTestCase inherit from KbdZRAMTestCase
- New version - 2.11


Thanks to all our contributors.

Vratislav Podzimek, 2017-07-31


Libblockdev 2.10
----------------

New minor release of libblockdev library adding some new functionality in the
crypto, fs and part plugins and fixing various issues and bugs.

**Notable changes**

- crypto

  - support for opening and closing TrueCrypt/VeraCrypt volumes: ``bd_crypto_tc_open``
    and ``bd_crypto_tc_close``

- fs

  - new functions for checking of filesystem functions availability:  ``bd_fs_can_resize``,
    ``bd_fs_can_check`` and ``bd_fs_can_repair``

  - new generic function for filesystem repair and check: ``bd_fs_repair`` and ``bd_fs_check``

- part

  - newly added support for partition resizing: ``bd_part_resize_part``


**Full list of changes**

Kai Lüke (6):

- Size in bytes for xfs_resize_device
- Query functions for FS resize and repair support
- Generic Check and Repair Functions
- Add partition resize function
- Query setting FS label support and generic relabeling
- Specify tolerance for partition size

Tony Asleson (3):

- kbd.c: Make bd_kbd_bcache_create work without abort
- kbd.c: Code review corrections
- bcache tests: Remove FEELINGLUCKY checks

Tristan Van Berkom (2):

- Fixed include for libvolume_key.h
- src/plugins/Makefile.am: Remove hard coded include path in /usr prefix

Vratislav Podzimek (12):

- Try RO mount also if we get EACCES
- Adapt to a change in behaviour in new libmount
- Add functions for opening/closing TrueCrypt/VeraCrypt volumes
- Update the project/source URL in the spec file
- Compile everything with the C99 standard
- Do not strictly require all FS utilities
- Check resulting FS size in tests for generic FS resize
- Only use the exact constraint if not using any other
- Do not verify vfat FS' size after generic resize
- Limit the requested partition size to maximum possible
- Only enable partition size tolerance with alignment
- New version - 2.10

squimrel (1):

- Ignore parted warnings if possible

Thanks to all our contributors.

Vratislav Podzimek, 2017-07-05
