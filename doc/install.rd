# -*- rd -*-

= Install --- How to install milter manager

== About this document

This document describes how to install milter manager.

== Dependencies

This section describes softwares that are depended on
milter manager.

=== Required

milter manager depends on the following softwares. They
should be installed before building milter manager.

  * GLib >= 2.12.3
  * Ruby >= 1.8.5 (1.9.x isn't supported)
  * Ruby/GLib2 (Ruby-GNOME2) >= 0.16.0

=== Optional: Testing

To run milter manager's unit tests, the following softwares
are needed. They are needed for running unit tests but not
needed for running milter manager.

  * Cutter >= 1.0.6 (not released yet)
  * LCOV

=== Optional: Graph

milter manager provides a feature that generates graphs for
milter's status and so on from milter manager log. The
following softwares are required to generate graphs but they
are not required for running milter manager.

 * RRDtool
 * RRDtool's Ruby bindings

=== Optional: Web interface for administration

milter manager can be ran without editing configuration if
you use system standard package system. But you need to
modify configuration if you install a milter without using
package system or want to tune milter manager behavior.

milter manager provides Web interface for modifying
simple configurations. You can modify configurations by
browser. The Web interface is optional because modifying
configurations can be done with editing configuration
file. The following softwares are required for the Web
interface.

  * RubyGems >= 1.3.1
  * Ruby on Rails 2.2.2
  * SQLite3
  * SQLite3's Ruby bindings
  * Ruby-Locale for Ruby on Rails
  * Passenger

== milter-manager

milter-manager is a core program of the milter manager
package. milter-manager works as a milter and connects to
MTA and child miltres.

Here are documents about how to install milter-manager to
your platform:

  * ((<Ubuntu|install-to-ubuntu.rd>))
  * ((<CentOS|install-to-centos.rd>))
  * ((<FreeBSD|install-to-freebsd.rd>))
#   * ((<Etc|install-to-others.rd>))

== milter-manager-log-analyzer

milter-manager-log-analyzer is a program that generates
graphs from milter-manager's log. Installing
milter-manager-log-analyzer is optional.

To confirm milter behavior, we can use
milter-manager-log-analyzer. It's convenient for confirming
new milter's effect and milter result in chronological order
visually.

milter-manager-log-analyzer analyzes milter-manager logs
from syslog output. It uses
((<RRDtool|URL:http://oss.oetiker.ch/rrdtool/>)) to generate
graphs. milter-manager-log-analyzer analyzes the logs
periodically by cron.

Here are documents about how to install
milter-manager-log-analyzer. They also describes about how
to install Web interface for administration.

  * ((<Ubuntu|install-options-to-ubuntu.rd>))
  * ((<CentOS|install-options-to-centos.rd>))
  * ((<FreeBSD|install-options-to-freebsd.rd>))

== milter manager admin

milter manager admin is a Web interface for administrating
milter-manager. Installing milter manager admin is optional.

With milter manager admin, we can modify milter-manager
configuration. For example, we can enable or disable child
milter, change child milter's applicable condition and so
on. It's useful for trying to find the best match
countermeasure against just mail.

To provide user-friendly and simple interface, milter
manager admin doesn't provide all features which are be able
to in configuration file. For example, we can't edit
applicable condition in browser.

Here are documents about how to install milter manager
admin. They also describes about how to install
milter-manager-log-analyzer.

  * ((<Ubuntu|install-options-to-ubuntu.rd>))
  * ((<CentOS|install-options-to-centos.rd>))
  * ((<FreeBSD|install-options-to-freebsd.rd>))
