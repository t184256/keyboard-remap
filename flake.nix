{
  description = "t184256's keyboard remapper";

  inputs.flake-utils.url = "github:numtide/flake-utils";
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/release-21.05";

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let pkgs = nixpkgs.legacyPackages.${system}; in
        rec {
          # defaultPackage = ...
          devShell = import ./shell.nix { inherit pkgs; };
        }
      );

    # defaultPackage...
}
