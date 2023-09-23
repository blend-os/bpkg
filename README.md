<div align="center">

<h1>bpkg</h1>
<br>
<a href="https://git.blendos.co/blendOS/bpkg/-/pipelines/latest"><img alt="Pipeline badge" src="https://git.blendos.co/blendos/bpkg/badges/main/pipeline.svg?ignore_skipped=true"></a>
<a href="https://git.blendos.co/blendOS/bpkg/-/archive/main/bpkg-main.tar.gz"><img alt="Download Badge" src="https://img.shields.io/badge/bpkg-download-%233eb787"></a>
<a href="https://docs.blendos.co/docs/utilities/bpkg"><img alt="bpkg docs" src="https://img.shields.io/badge/bpkg-documentation-%233eb787"></a>
</br>
</div>

<hr>

`bpkg` is a universal package manager for BlendOS.

`bpkg` allows you to automatically search for a package through the repositories of your containers and automaticallly selects the best package according to your preference.  

**NOTE:** This program is alpha software. You may experience issues while using it. 

## Install

Download `bpkg` [**here**](https://git.blendos.co/blendOS/bpkg/-/archive/main/bpkg-main.tar.gz).


## Usage

### Install a package

```
bpkg install <package> [-c <container>]
```

This will search for the package in your installed distros and install it from the first package manager it finds by your order of preference, though you can specify a specific container.  

### Remove a package

```
bpkg remove <package> [-c <container>]
```

This will remove a package that you installed from a container of your choice or from the first container in your list the package is found in.  

### Update packages

```
bpkg update [-c <container>]
```

This will update all the packages in all your containers, or you can specify a specific one. If update_flatpak is set to true in the config, this will also update your flatpaks.  

### Package Search

```
bpkg search <package> [-c <container>]
```

You can search for a package in all of your containers, or specify a specific one.  

### Container list

```
bpkg list-containers
```

Lists all containers on your system (even if they aren't in the config).  

### Config Regeneration

```
bpkg overwrite-config
```

This will pull all your containers and generate a new config file, overwriting your current one. It is recommended to run this after creating or deleting containers.
