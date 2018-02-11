/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libetonyek project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef IWORKENUM_H_INCLUDED
#define IWORKENUM_H_INCLUDED

namespace libetonyek
{

enum IWORKAlignment
{
  IWORK_ALIGNMENT_LEFT,
  IWORK_ALIGNMENT_RIGHT,
  IWORK_ALIGNMENT_CENTER,
  IWORK_ALIGNMENT_JUSTIFY,
  IWORK_ALIGNMENT_AUTOMATIC
};

enum IWORKBaseline
{
  IWORK_BASELINE_NORMAL,
  IWORK_BASELINE_SUB,
  IWORK_BASELINE_SUPER
};

enum IWORKBorderType
{
  IWORK_BORDER_TYPE_NONE,
  IWORK_BORDER_TYPE_TOP,
  IWORK_BORDER_TYPE_BOTTOM,
  IWORK_BORDER_TYPE_TOP_AND_BOTTOM,
  IWORK_BORDER_TYPE_ALL
};

enum IWORKBorderStroke
{
  IWORK_BORDER_STROKE_NONE,
  IWORK_BORDER_STROKE_SOLID,
  IWORK_BORDER_STROKE_DOTTED,
  IWORK_BORDER_STROKE_DASHED
};

enum IWORKBreakType
{
  IWORK_BREAK_NONE,
  IWORK_BREAK_LINE,
  IWORK_BREAK_COLUMN,
  IWORK_BREAK_PAGE
};

enum IWORKCapitalization
{
  IWORK_CAPITALIZATION_NONE,
  IWORK_CAPITALIZATION_ALL_CAPS,
  IWORK_CAPITALIZATION_SMALL_CAPS,
  IWORK_CAPITALIZATION_TITLE
};

enum IWORKLineCap
{
  IWORK_LINE_CAP_NONE,
  IWORK_LINE_CAP_BUTT,
  IWORK_LINE_CAP_ROUND
};

enum IWORKLineJoin
{
  IWORK_LINE_JOIN_NONE,
  IWORK_LINE_JOIN_MITER,
  IWORK_LINE_JOIN_ROUND
};

enum IWORKCellType
{
  IWORK_CELL_TYPE_NUMBER,
  IWORK_CELL_TYPE_TEXT,
  IWORK_CELL_TYPE_DATE_TIME,
  IWORK_CELL_TYPE_DURATION,
  IWORK_CELL_TYPE_BOOL
};

enum IWORKCellNumberType
{
  IWORK_CELL_NUMBER_TYPE_CURRENCY,
  IWORK_CELL_NUMBER_TYPE_PERCENTAGE,
  IWORK_CELL_NUMBER_TYPE_SCIENTIFIC,
  IWORK_CELL_NUMBER_TYPE_DOUBLE
};

enum IWORKImageType
{
  IWORK_IMAGE_TYPE_ORIGINAL_SIZE,
  IWORK_IMAGE_TYPE_STRETCH,
  IWORK_IMAGE_TYPE_TILE,
  IWORK_IMAGE_TYPE_SCALE_TO_FILL,
  IWORK_IMAGE_TYPE_SCALE_TO_FIT
};

enum IWORKGradientType
{
  IWORK_GRADIENT_TYPE_LINEAR,
  IWORK_GRADIENT_TYPE_RADIAL
};

enum IWORKVerticalAlignment
{
  IWORK_VERTICAL_ALIGNMENT_TOP,
  IWORK_VERTICAL_ALIGNMENT_MIDDLE,
  IWORK_VERTICAL_ALIGNMENT_BOTTOM
};

enum IWORKStrokeType
{
  IWORK_STROKE_TYPE_NONE,
  IWORK_STROKE_TYPE_SOLID,
  IWORK_STROKE_TYPE_DASHED,
  IWORK_STROKE_TYPE_AUTO
};

enum IWORKLabelNumFormat
{
  IWORK_LABEL_NUM_FORMAT_NUMERIC,
  IWORK_LABEL_NUM_FORMAT_ALPHA,
  IWORK_LABEL_NUM_FORMAT_ALPHA_LOWERCASE,
  IWORK_LABEL_NUM_FORMAT_ROMAN,
  IWORK_LABEL_NUM_FORMAT_ROMAN_LOWERCASE
};

enum IWORKLabelNumFormatSurrounding
{
  IWORK_LABEL_NUM_FORMAT_SURROUNDING_NONE,
  IWORK_LABEL_NUM_FORMAT_SURROUNDING_PARENTHESIS,
  IWORK_LABEL_NUM_FORMAT_SURROUNDING_DOT
};

enum IWORKFieldType
{
  IWORK_FIELD_DATETIME,
  IWORK_FIELD_FILENAME,
  IWORK_FIELD_PAGECOUNT,
  IWORK_FIELD_PAGENUMBER
};

enum IWORKWrapDirection
{
  IWORK_WRAP_DIRECTION_BOTH,
  IWORK_WRAP_DIRECTION_LEFT,
  IWORK_WRAP_DIRECTION_RIGHT
};

enum IWORKWrapStyle
{
  IWORK_WRAP_STYLE_REGULAR,
  IWORK_WRAP_STYLE_TIGHT
};

enum IWORKWrapType
{
  IWORK_WRAP_TYPE_ALIGNED,
  IWORK_WRAP_TYPE_DIRECTIONAL,
  IWORK_WRAP_TYPE_LARGEST,
  IWORK_WRAP_TYPE_NEITHER,
  IWORK_WRAP_TYPE_UNALIGNED
};

}

#endif //  IWORKENUM_H_INCLUDED

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
