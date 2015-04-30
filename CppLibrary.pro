TEMPLATE = subdirs

SUBDIRS = \
    src \
    tests

tests.depends = src

DESTDIR=./
