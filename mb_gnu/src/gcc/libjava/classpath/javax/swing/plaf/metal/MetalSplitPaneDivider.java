/* MetalSplitPaneDivider.java
Copyright (C) 2005 Free Software Foundation, Inc.

This file is part of GNU Classpath.

GNU Classpath is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Classpath is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Classpath; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301 USA.

Linking this library statically or dynamically with other modules is
making a combined work based on this library.  Thus, the terms and
conditions of the GNU General Public License cover the whole
combination.

As a special exception, the copyright holders of this library give you
permission to link this library with independent modules to produce an
executable, regardless of the license terms of these independent
modules, and to copy and distribute the resulting executable under
terms of your choice, provided that you also meet, for each linked
independent module, the terms and conditions of the license of that
module.  An independent module is a module which is not derived from
or based on this library.  If you modify this library, you may extend
this exception to your version of the library, but you are not
obligated to do so.  If you do not wish to do so, delete this
exception statement from your version. */

package javax.swing.plaf.metal;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;

import javax.swing.plaf.basic.BasicSplitPaneDivider;

/**
 * The divider that is used by the MetalSplitPaneUI.
 *
 * @author Roman Kennke (roman@kennke.org)
 *
 */
class MetalSplitPaneDivider extends BasicSplitPaneDivider
{
  /** The dark color in the pattern. */
  Color dark;

  /** The light color in the pattern. */
  Color light;

  /**
   * Creates a new instance of MetalSplitPaneDivider.
   *
   * @param ui the <code>MetalSplitPaneUI</code> that uses this divider
   */
  public MetalSplitPaneDivider(MetalSplitPaneUI ui, Color light, Color dark)
  {
    super(ui);
    this.light = light;
    this.dark = dark;
  }

  /**
   * Paints the divider.
   *
   * @param g the <code>Graphics</code> context to use for painting
   */
  public void paint(Graphics g)
  {
    //super.paint(g);
    Dimension s = getSize();
    MetalUtils.fillMetalPattern(splitPane, g, 2, 2, s.width - 4, s.height - 4,
                                light, dark);
  }
}
