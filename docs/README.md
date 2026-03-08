# AVOE Documentation
## Contents
- Overview
- Introduction
- Sensors
- Motors
- Networking
- Vehicle Setup
- Frontends and Gamepads 

## Overview
The Autonomous Vehicle Operating Environment is a project headed by the University of Rhode Island Hydrobotics team that aims to be a minimilist robotics middleware suite for AUVs. AVOE is designed to run on Linux but is not distrobution specific, in fact, its requirements are quite minimal and it should run under any modern Linux distribution.

## Introduction
AVOE should be considered as a set of libraries that will help you build control software for an AUV. At the core AVOE provides generalized components for declaring sensors and motors along with an underlying subsystem that provides networking, logging, tools to build a ground interface (deckbox), and reference components in the form of plugins for extended functionality. While our codebase contains drivers and other code for our usecases, these drivers should not be considered core to AVOE, hence why they are in `plugins/`.
