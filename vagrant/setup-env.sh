#!/bin/bash
set -e

( cd /vagrant/conf/ && sudo cp -r --parents * / )

echo "Configuration finished"
