# hekate - Nyx　日本語バージョン

![Hekateの写真](https://user-images.githubusercontent.com/3665130/60391760-bc1e8c00-9afe-11e9-8b7a-b065873081b2.png)


カスタムグラフィカルNintendo Switchブートローダー、ファームウェア パッチャー、ツールなど。



- [特徴](#特徴)
- [ブートローダーのフォルダとファイル](#bootloader-folders-and-files)
- [ブートローダーの設定](#bootloader-configuration)
  * [hekateグローバル設定](#hekate-global-configuration-keysvalues-when-entry-is-config)
  * [起動エントリ](#boot-entry-keyvalue-combinations)
  * [Exosphèreの起動エントリ](#boot-entry-keyvalue-combinations-for-exosphère)
  * [ペイロード](#payload-storage)
  * [Nyx設定](#nyx-configuration-keysvalues-nyxini)



## 特徴

- **タッチスクリーンとジョイコン入力をサポートし、完全に設定可能でグラフィカル**
- **ランチャーのスタイル、背景と色のテーマ**
- **HOS（Switch OS）ブートローダー** -- CFW Sys/Emu、OFW SysとStock Sys用
- **AndroidとLinuxのブートローダー**
- **ペイロードランチャー**
- **eMMC/emuMMCのバックアップ/リストアツール**
- **SDカードのパーティション管理ツール** -- HOS（Sys/emuMMC）、Android、Linuxの組み合わせ用にSDカードを準備しフォーマットします。
- **emuMMCの作成と管理** -- 既存のemuMMCを移行し、修正することもできます。
- **Switch用AndroidとLinuxをフラッシュ**
- **SDカード/eMMC/emuMMCをUSB大容量記憶装置(UMS)に** -- SwitchをSDカードリーダーに変換できます
- **USBゲームパッド** -- ジョイコンを搭載したSwitchをUSB HIDゲームパッドに変換
- **ハードウェアと周辺機器の情報** -- (SoC、ヒューズ、RAM、画面、タッチパネル、eMMC, SDカード, バッテリー, PSU, 充電器)
- **その他多くのツール** -- アーカイブビットの修正, タッチパネルの較正, SDカード/eMMCのベンチマーク, AutoRCMの有効化など


## Bootloader folders and files

| フォルダー / ファイル             | 説明                                                           |
| ------------------------ | --------------------------------------------------------------------- |
| bootloader               | メインのフォルダー                                                          |
|  \|__ bootlogo.bmp       | `logopath`が指定されていない場合に使用されます。スキップ可能。 |
|  \|__ hekate_ipl.ini     | `Launch`メニュー内の主なブートローダー設定と起動エントリ。      |
|  \|__ nyx.ini            | Nyx GUIの設定。                                                 |
|  \|__ patches.ini        | 外部パッチを追加します。スキップ可能。[ここ](./res/patches_template.ini)にテンプレートがあります。  |
|  \|__ update.bin         | 新しい場合は起動時にロードされます。通常はモッドチップ用です。初回起動時に自動更新および作成されます。|
| bootloader/ini/          | 個々のiniファイル。`More config`メニュー。自動起動がサポートされています。  |
| bootloader/res/          | Nyxのユーザリソース、アイコンなど。                                   |
|  \|__ background.bmp     | Nyx - カスタム背景。好きなものを指定できます。                               |
|  \|__ icon_switch.bmp    | Nyx - CFWのデフォルトのアイコン。                                          |
|  \|__ icon_payload.bmp   | Nyx - ペイロードのデフォルトのアイコン。                                      |
| bootloader/sys/          | hekateとNyxのシステムモジュールのフォルダー。                                 |
|  \|__ emummc.kipm        | emuMMC KIP1モジュール 重要！                                       |
|  \|__ libsys_lp0.bso     | LP0(スリープモード)モジュール 重要！                                   |
|  \|__ libsys_minerva.bso | Minervaトレーニングセル。 DRAM周波数トレーニングに使用されます。 重要！  |
|  \|__ nyx.bin            | Nyx - hekateのGUI 重要！                                       |
|  \|__ res.pak            | Nyxのリソースパッケージ 重要！                                    |
|  \|__ thk.bin            | Atmosphère Tsec Hovi Keygen. 重要！                              |
| bootloader/screenshots/  | Nyxのスクリーンショットが保存されるフォルダー                                |
| bootloader/payloads/     | `ペイロード`メニューの場合。すべてのCFWブートローダー、ツール、Linuxペイロードがサポートされています。自動ブートは、ini に含めることによってのみサポートされます。 |
| bootloader/libtools/     | Reserved                                                              |



## Bootloader configuration

The bootloader can be configured via 'bootloader/hekate_ipl.ini' (if it is present on the SD card). Each ini section represents a boot entry, except for the special section 'config' that controls the global configuration.


There are four possible type of entries. "**[ ]**": Boot entry, "**{ }**": Caption, "**#**": Comment, "*newline*": .ini cosmetic newline.


**You can find a template [Here](./res/hekate_ipl_template.ini)**


### hekate Global Configuration keys/values (when entry is *[config]*):

| Config option      | Description                                                |
| ------------------ | ---------------------------------------------------------- |
| autoboot=0         | 0: Disable, #: Boot entry number to auto boot.             |
| autoboot_list=0    | 0: Read `autoboot` boot entry from hekate_ipl.ini, 1: Read from ini folder (ini files are ASCII ordered). |
| bootwait=3         | 0: Disable (It also disables bootlogo. Having **VOL-** pressed since injection goes to menu.), #: Time to wait for **VOL-** to enter menu. Max: 20s. |
| noticker=0         | 0: Animated line is drawn during custom bootlogo, signifying time left to skip to menu. 1: Disable. |
| autohosoff=1       | 0: Disable, 1: If woke up from HOS via an RTC alarm, shows logo, then powers off completely, 2: No logo, immediately powers off.|
| autonogc=1         | 0: Disable, 1: Automatically applies nogc patch if unburnt fuses found and a >= 4.0.0 HOS is booted. |
| bootprotect=0      | 0: Disable, 1: Protect bootloader folder from being corrupted by disallowing reading or editing in HOS. |
| updater2p=0        | 0: Disable, 1: Force updates (if needed) the reboot2payload binary to be hekate. |
| backlight=100      | Screen backlight level. 0-255.                             |


### Boot entry key/value combinations:

| Config option          | Description                                                |
| ---------------------- | ---------------------------------------------------------- |
| warmboot={FILE path}   | Replaces the warmboot binary                               |
| secmon={FILE path}     | Replaces the security monitor binary                       |
| kernel={FILE path}     | Replaces the kernel binary                                 |
| kip1={FILE path}       | Replaces/Adds kernel initial process. Multiple can be set. |
| kip1={FOLDER path}/*   | Loads every .kip/.kip1 inside a folder. Compatible with single kip1 keys. |
| fss0={FILE path}       | Takes an Atmosphere `package3` binary (formerly fusee-secondary.bin) and `extracts` all needed parts from it. kips, exosphere, warmboot and mesophere if enabled. |
| fss0experimental=1     | Enables loading of experimental content from a FSS0 storage |
| exofatal={FILE path}   | Replaces the exosphere fatal binary for Mariko             |
| ---------------------- | ---------------------------------------------------------- |
| kip1patch=patchname    | Enables a kip1 patch. Specify with multiple lines and/or in one line with `,` as separator. If actual patch is not found, a warning will show up |
| emupath={FOLDER path}  | Forces emuMMC to use the selected one. (=emuMMC/RAW1, =emuMMC/SD00, etc). emuMMC must be created by hekate because it uses the raw_based/file_based files. |
| emummcforce=1          | Forces the use of emuMMC. If emummc.ini is disabled or not found, then it causes an error. |
| emummc_force_disable=1 | Disables emuMMC, if it's enabled.                           |
| stock=1                | Disables unneeded kernel patching and CFW kips when running stock or semi-stock. `If emuMMC is enabled, emummc_force_disable=1` is required. emuMMC is not supported on stock. If additional KIPs are needed other than OFW's, you can define them with `kip1` key. No kip should be used that relies on Atmosphère patching, because it will hang. If `NOGC` is needed, use `kip1patch=nogc`. |
| fullsvcperm=1          | Disables SVC verification (full services permission). Doesn't work with Mesosphere as kernel. |
| debugmode=1            | Enables Debug mode. Obsolete when used with exosphere as secmon. |
| atmosphere=1           | Enables Atmosphère patching. Not needed when `fss0` is used. |
| ---------------------- | ---------------------------------------------------------- |
| payload={FILE path}    | Payload launching. Tools, Android/Linux, CFW bootloaders, etc. Any key above when used with that, doesn't get into account. |
| ---------------------- | ---------------------------------------------------------- |
| l4t=1                  | L4T Linux/Android native launching.                        |
| boot_prefixes={FOLDER path} | L4T bootstack directory.                              |
| ram_oc=0               | L4T RAM Overclocking. Check README_CONFIG.txt for more info. |
| uart_port=0            | Enables logging on serial port for L4T uboot/kernel.       |
| Additional keys        | Each distro supports more keys. Check README_CONFIG.txt  for more info. |
| ---------------------- | ---------------------------------------------------------- |
| id=IDNAME              | Identifies boot entry for forced boot via id. Max 7 chars. |
| logopath={FILE path}   | If it exists, it will load the specified bitmap. Otherwise `bootloader/bootlogo.bmp` will be used if exists |
| icon={FILE path}       | Force Nyx to use the icon defined here. If this is not found, it will check for a bmp named as the boot entry ([Test 2] -> `bootloader/res/Test 2.bmp`). Otherwise defaults will be used. |


**Note1**: When using the wildcard (`/*`) with `kip1` you can still use the normal `kip1` after that to load extra single kips.

**Note2**: When using FSS0 it parses exosphere, warmboot and all core kips. You can override the first 2 by using `secmon`/`warmboot` after defining `fss0`.
You can define `kip1` to load an extra kip or many via the wildcard (`/*`) usage.

**Warning**: Careful when you define *fss0 core* kips when using `fss0` or the folder (when using `/*`) includes them.
This is in case the kips are incompatible between them. If compatible, you can override `fss0` kips with no issues (useful for testing with intermediate kip changes). In such cases, the `kip1` line must be under `fss0` line.


### Boot entry key/value combinations for Exosphère:

| Config option          | Description                                                |
| ---------------------- | ---------------------------------------------------------- |
| nouserexceptions=1     | Disables usermode exception handlers when paired with Exosphère. |
| userpmu=1              | Enables user access to PMU when paired with Exosphère.     |
| cal0blank=1            | Overrides Exosphère config `blank_prodinfo_{sys/emu}mmc`. If that key doesn't exist, `exosphere.ini` will be used. |
| cal0writesys=1         | Overrides Exosphère config `allow_writing_to_cal_sysmmc`. If that key doesn't exist, `exosphere.ini` will be used. |
| usb3force=1            | Overrides system settings mitm config `usb30_force_enabled`. If that key doesn't exist, `system_settings.ini` will be used. |


**Note**: `cal0blank`, `cal0writesys`, `usb3force`, as stated override the `exosphere.ini` or `system_settings.ini`. 0: Disable, 1: Enable, Key Missing: Use original value.


**Note2**: `blank_prodinfo_{sys/emu}mmc`, `allow_writing_to_cal_sysmmc` and `usb30_force_enabled` in `exosphere.ini` and `system_settings.ini` respectively, are the only atmosphere config keys that can affect hekate booting configuration externally, **if** the equivalent keys in hekate config are missing.


### Payload storage:

hekate has a boot storage in the binary that helps it configure it outside of BPMP enviroment:

| Offset / Name           | Description                                                       |
| ----------------------- | ----------------------------------------------------------------- |
| '0x94' boot_cfg         | bit0: `Force AutoBoot`, bit1: `Show launch log`, bit2: `Boot from ID`, bit3: `Boot to emuMMC`. |
| '0x95' autoboot         | If `Force AutoBoot`, 0: Force go to menu, else boot that entry.   |
| '0x96' autoboot_list    | If `Force AutoBoot` and `autoboot` then it boots from ini folder. |
| '0x97' extra_cfg        | When menu is forced: bit5: `Run UMS`.                             |
| '0x98' xt_str[128]      | Depends on the set cfg bits.                                      |
| '0x98' ums[1]           | When `Run UMS` is set, it will launch the selected UMS. 0: SD, 1: eMMC BOOT0, 2: eMMC BOOT1, 3: eMMC GPP, 4: emuMMC BOOT0, 5: emuMMC BOOT1, 6: emuMMC GPP,  |
| '0x98' id[8]            | When `Boot from ID` is set, it will search all inis automatically and find the boot entry with that id and boot it. Must be NULL terminated. |
| '0xA0' emummc_path[120] | When `Boot to emuMMC` is set, it will override the current emuMMC (boot entry or emummc.ini). Must be NULL terminated. |


### Nyx Configuration keys/values (nyx.ini):

| Config option      | Description                                                |
| ------------------ | ---------------------------------------------------------- |
| themebg=2d2d2d     | Sets Nyx background color in HEX. EXPERIMENTAL.            |
| themecolor=167     | Sets Nyx color of text highlights.                         |
| entries5col=0      | 1: Sets Launch entry columns from 4 to 5 per line. For a total of 10 entries. |
| timeoff=100        | Sets time offset in HEX. Must be in HOS epoch format       |
| homescreen=0       | Sets home screen. 0: Home menu, 1: All configs (merges Launch and More configs), 2: Launch, 3: More Configs. |
| verification=1     | 0: Disable Backup/Restore verification, 1: Sparse (block based, fast and mostly reliable), 2: Full (sha256 based, slow and 100% reliable). |
| ------------------ | ------- The following options can only be edited in nyx.ini ------- |
| umsemmcrw=0        | 1: eMMC/emuMMC UMS will be mounted as writable by default. |
| jcdisable=0        | 1: Disables Joycon driver completely.                      |
| jcforceright=0     | 1: Forces right joycon to be used as main mouse control.   |
| bpmpclock=1        | 0: Auto, 1: Fastest, 2: Faster, 3: Fast. Use 2 or 3 if Nyx hangs or some functions like UMS/Backup Verification fail. |


```
hekate  (c) 2018,      naehrwert, st4rk.
        (c) 2018-2022, CTCaer.

Nyx GUI (c) 2019-2022, CTCaer.

Thanks to: derrek, nedwill, plutoo, shuffle2, smea, thexyz, yellows8.
Greetings to: fincs, hexkyz, SciresM, Shiny Quagsire, WinterMute.

Open source and free packages used:
 - FatFs R0.13a, Copyright (c) 2017, ChaN
 - bcl-1.2.0, Copyright (c) 2003-2006, Marcus Geelnard
 - Atmosphère (Exosphere types/panic, prc id kernel patches),
   Copyright (c) 2018-2019, Atmosphère-NX
 - elfload, Copyright (c) 2014 Owen Shepherd, Copyright (c) 2018 M4xw
 - Littlev Graphics Library, Copyright (c) 2016 Gabor Kiss-Vamosi

                         ___
                      .-'   `'.
                     /         \
                     |         ;
                     |         |           ___.--,
            _.._     |0) = (0) |    _.---'`__.-( (_.
     __.--'`_.. '.__.\    '--. \_.-' ,.--'`     `""`
    ( ,.--'`   ',__ /./;   ;, '.__.'`    __
    _`) )  .---.__.' / |   |\   \__..--""  """--.,_
   `---' .'.''-._.-'`_./  /\ '.  \ _.--''````'''--._`-.__.'
         | |  .' _.-' |  |  \  \  '.               `----`
          \ \/ .'     \  \   '. '-._)
           \/ /        \  \    `=.__`'-.
           / /\         `) )    / / `"".`\
     , _.-'.'\ \        / /    ( (     / /
      `--'`   ) )    .-'.'      '.'.  | (
             (/`    ( (`          ) )  '-;   [switchbrew]
```
