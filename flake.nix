{
  description = "t184256's keyboard remapper";

  inputs.flake-utils.url = "github:numtide/flake-utils";
  inputs.nixpkgs.url = "github:NixOS/nixpkgs";

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let pkgs = nixpkgs.legacyPackages.${system}; in
        rec {
          defaultPackage = pkgs.stdenv.mkDerivation {
            name = "keyboard-remap";
            nativeBuildInputs = with pkgs; [ python3 libevdev pkgconfig ];
            prapagatedBuildInputs = with pkgs; [ libevdev ];
            src = ./.;
            patchPhase = ''
              patchShebangs ./preprocessor.py
            '';
            compilePhase = ''
              make
            '';
            installPhase = ''
              mkdir -p $out/bin
              cp ./keyboard-remap-onemix $out/bin/
              cp ./keyboard-remap-tablet $out/bin/
              cp ./keyboard-remap-jap $out/bin/
              cp ./keyboard-remap.sh $out/bin/keyboard-remap
              substituteInPlace $out/bin/keyboard-remap \
                --replace keyboard-remap-onemix $out/bin/keyboard-remap-onemix
            '';
          };
          devShell = import ./shell.nix { inherit pkgs; };
        }
      );

    # defaultPackage...
}
