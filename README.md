
## LLVM14 and Later
```
wget https://heroims.github.io/obfuscator/LegacyPass/ollvm14.patch
git clone -b release/14.x git@github.com:llvm/llvm-project.git
cd llvm-project
git apply ../ollvm14.patch
```

## Please have a look at the [wiki](https://github.com/heroims/obfuscator/wiki)!

You can cite Obfuscator-LLVM using the following Bibtex entry:

```
@INPROCEEDINGS{ieeespro2015-JunodRWM,
  author={Pascal Junod and Julien Rinaldini and Johan Wehrli and Julie Michielin},
  booktitle={Proceedings of the {IEEE/ACM} 1st International Workshop on Software Protection, {SPRO'15}, Firenze, Italy, May 19th, 2015},
  editor = {Brecht Wyseur},
  publisher = {IEEE},
  title={Obfuscator-{LLVM} -- Software Protection for the Masses},
  year={2015},
  pages={3--9},
  doi={10.1109/SPRO.2015.10},
}
```


