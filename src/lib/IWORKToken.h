/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libetonyek project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef IWORKTOKEN_H_INCLUDED
#define IWORKTOKEN_H_INCLUDED

#include <boost/static_assert.hpp>

#include "IWORKTokenInfo.h"

namespace libetonyek
{

class IWORKTokenizer;

namespace IWORKToken
{

enum
{
  INVALID_TOKEN = 0,
  FIRST_TOKEN = IWORKTokenInfo<IWORKParser>::first,

  // namespace prefixes
  sf,
  sfa,

  // elements
  SFTCellStylePropertyNumberFormat,
  SFTCellStylePropertyDateTimeFormat,
  SFTStrokeProperty,
  alignment,
  anon_styles,
  attachment,
  attachment_ref,
  attachments,
  authors,
  baselineShift,
  bezier,
  bezier_path,
  bezier_ref,
  body_placeholder_ref,
  bold,
  cached_data,
  calc_engine,
  callout2_path,
  capitalization,
  category_title,
  cell_date,
  cell_style,
  cell_style_ref,
  characterstyle,
  characterstyle_ref,
  chart_column_names,
  chart_row_names,
  chart_info,
  chart_model_object,
  chart_name,
  chart_type,
  color,
  column,
  columns,
  column_label_formulas,
  comment,
  connection_line,
  connection_path,
  connection_style,
  container_hint,
  content,
  crbr,
  ct,
  d,
  data,
  data_formulas,
  data_ref,
  datasource,
  date_format,
  drawable_shape,
  drawables,
  du,
  editable_bezier_path,
  element,
  evenPageMaster,
  f,
  fill,
  filtered,
  filtered_image,
  firstLineIndent,
  firstPageMaster,
  fmt,
  fo,
  fontColor,
  fontName,
  fontSize,
  footer,
  footers,
  footnote,
  footnotes,
  footnotebr,
  footnote_mark,
  format_base,
  format_base_places,
  format_type,
  format_string,
  format_decimal_places,
  format_currency_code,
  format_negative_style,
  format_show_thousands_separator,
  format_fraction_accuracy,
  format_use_accounting_style,
  formula_chart_model,
  fs,
  g,
  geometry,
  graphic_style,
  graphic_style_ref,
  grid,
  grid_column,
  grid_row,
  gridline_index,
  group,
  head,
  header,
  headers,
  headline_style,
  href,
  id,
  image,
  image_media,
  intratopicbr,
  italic,
  keepLinesTogether,
  keepWithNext,
  keywords,
  language,
  layer,
  layer_ref,
  layers,
  layout,
  layoutMargins,
  layoutstyle,
  layoutstyle_ref,
  leftIndent,
  leveled,
  line,
  lineSpacing,
  linespacing,
  link,
  liststyle,
  liststyle_ref,
  lnbr,
  media,
  metadata,
  movie_media,
  mutable_array,
  n,
  naturalSize,
  number,
  number_format,
  oddPageMaster,
  other_datas,
  outline,
  p,
  padding,
  pageBreakBefore,
  pagemaster,
  paragraphBorderType,
  paragraphFill,
  paragraphStroke,
  paragraphstyle,
  paragraphstyle_ref,
  parent_ref,
  path,
  pattern,
  placeholder_style,
  placeholder_style_ref,
  point,
  point_path,
  position,
  property_map,
  proxy_master_layer,
  r,
  rightIndent,
  rn,
  rows,
  row_label_formulas,
  s,
  scalar_path,
  section,
  sectionstyle,
  sectionstyle_ref,
  self_contained_movie,
  shape,
  size,
  slide_style,
  so,
  spaceAfter,
  spaceBefore,
  span,
  start_index,
  stop_index,
  sticky_note,
  strikethru,
  string,
  stroke,
  style,
  style_run,
  styles,
  stylesheet,
  stylesheet_ref,
  superscript,
  t,
  tab,
  tabs,
  tabs_ref,
  tabstop,
  tabular_info,
  tabular_model,
  tabular_style,
  tail,
  text,
  textBackground,
  text_body,
  text_storage,
  title,
  title_placeholder_ref,
  tracking,
  type,
  underline,
  unfiltered,
  unfiltered_ref,
  vector_style,
  vector_style_ref,
  vertical_gridline_styles,
  widowControl,

  // attributes
  ID,
  IDREF,
  a,
  align,
  amt,
  angle,
  aspectRatioLocked,
  b,
  bottom,
  cap,
  col_span,
  cornerRadius,
  displayname,
  equal_columns,
  frame_h,
  frame_w,
  frame_x,
  frame_y,
  h,
  height,
  hfs_type,
  horizontalFlip,
  horizontal_gridline_styles,
  ident,
  join,
  kind,
  left,
  locked,
  mark,
  mode,
  name,
  numcols,
  numrows,
  parent_ident,
  pos,
  right,
  row_span,
  scalar,
  shearXAngle,
  shearYAngle,
  sizesLocked,
  spacing,
  tailAtCenter,
  tailPositionX,
  tailPositionY,
  tailSize,
  top,
  v,
  val,
  value_title,
  verticalFlip,
  w,
  width,
  x,
  y,

  // attribute values
  __multilingual,
  _0,
  _1,
  _1246774599,
  _1299148630,
  _1346651680,
  _1347307366,
  _1414088262,
  butt,
  double_,
  false_,
  miter,
  relative,
  star,
  true_,

  LAST_TOKEN
};

BOOST_STATIC_ASSERT(IWORKTokenInfo<IWORKParser>::last >= LAST_TOKEN);

enum Namespace
{
  NS_URI_SF = sf << 16,
  NS_URI_SFA = sfa << 16
};

const IWORKTokenizer &getTokenizer();

}

}

#endif // IWORKTOKEN_H_INCLUDED

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
