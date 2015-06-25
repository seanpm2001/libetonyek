/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libetonyek project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "IWORKPath.h"

#include <cassert>
#include <utility>

#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>

#include "libetonyek_utils.h"
#include "IWORKTypes.h"

using boost::cref;

using librevenge::RVNGPropertyList;
using librevenge::RVNGPropertyListVector;

using std::string;

namespace libetonyek
{

/** An element of path.
  */
class IWORKPath::Element
{
public:
  virtual ~Element() = 0;

  virtual Element *clone() const = 0;

  /** Test whether this element is equal to other.
    *
    * @note Because all implementations of this interface are directly
    * derived from it (i.e., thay have no subclasses), it is enough to
    * check if @c other has a compatible type, not that @c this and @c
    * other have the @em same type (which would require double
    * dispatch).
    *
    * @return true if @c this and @c other are equal.
    */
  virtual bool approxEqualsTo(const Element *other, double eps) const = 0;

  /** Transform this path element.
    *
    * @arg[in] tr the transformation
    */
  virtual void transform(const glm::dmat3 &tr) = 0;

  /** Create librevenge representation of this path element.
   */
  virtual void write(RVNGPropertyList &element) const = 0;
};

namespace
{

class MoveTo : public IWORKPath::Element
{
public:
  MoveTo(double x, double y);

  virtual MoveTo *clone() const;

  virtual bool approxEqualsTo(const Element *other, double eps) const;

  virtual void transform(const glm::dmat3 &tr);

  virtual void write(RVNGPropertyList &element) const;

private:
  double m_x;
  double m_y;
};

MoveTo::MoveTo(double x, double y)
  : m_x(x)
  , m_y(y)
{
}

MoveTo *MoveTo::clone() const
{
  return new MoveTo(*this);
}

bool MoveTo::approxEqualsTo(const Element *other, const double eps) const
{
  const MoveTo *const that = dynamic_cast<const MoveTo *>(other);

  if (that)
    return approxEqual(m_x, that->m_x, eps) && approxEqual(m_y, that->m_y, eps);

  return false;
}

void MoveTo::transform(const glm::dmat3 &tr)
{
  glm::dvec3 vec = tr * glm::dvec3(m_x, m_y, 1);

  m_x = vec[0];
  m_y = vec[1];

}

void MoveTo::write(RVNGPropertyList &element) const
{
  element.insert("librevenge:path-action", "M");
  element.insert("svg:x", pt2in(m_x));
  element.insert("svg:y", pt2in(m_y));
}

}

namespace
{

class LineTo : public IWORKPath::Element
{
public:
  LineTo(double x, double y);

  virtual LineTo *clone() const;

  virtual bool approxEqualsTo(const Element *other, double eps) const;

  virtual void transform(const glm::dmat3 &tr);

  virtual void write(RVNGPropertyList &element) const;

private:
  double m_x;
  double m_y;
};

LineTo::LineTo(const double x, const double y)
  : m_x(x)
  , m_y(y)
{
}

LineTo *LineTo::clone() const
{
  return new LineTo(*this);
}

bool LineTo::approxEqualsTo(const Element *other, const double eps) const
{
  const LineTo *const that = dynamic_cast<const LineTo *>(other);

  if (that)
    return approxEqual(m_x, that->m_x, eps) && approxEqual(m_y, that->m_y, eps);

  return false;
}

void LineTo::transform(const glm::dmat3 &tr)
{
  glm::dvec3 vec = tr * glm::dvec3(m_x, m_y, 1);

  m_x = vec[0];
  m_y = vec[1];
}

void LineTo::write(RVNGPropertyList &element) const
{
  element.insert("librevenge:path-action", "L");
  element.insert("svg:x", pt2in(m_x));
  element.insert("svg:y", pt2in(m_y));
}

}

namespace
{

class CurveTo : public IWORKPath::Element
{
public:
  CurveTo(double x1, double y1, double x2, double y2, double x, double y);

  virtual CurveTo *clone() const;

  virtual bool approxEqualsTo(const Element *other, double eps) const;

  virtual void transform(const glm::dmat3 &tr);

  virtual void write(RVNGPropertyList &element) const;

private:
  double m_x1;
  double m_y1;
  double m_x2;
  double m_y2;
  double m_x;
  double m_y;
};

CurveTo::CurveTo(const double x1, const double y1, const double x2, const double y2, const double x, const double y)
  : m_x1(x1)
  , m_y1(y1)
  , m_x2(x2)
  , m_y2(y2)
  , m_x(x)
  , m_y(y)
{
}

CurveTo *CurveTo::clone() const
{
  return new CurveTo(*this);
}

bool CurveTo::approxEqualsTo(const Element *other, const double eps) const
{
  const CurveTo *const that = dynamic_cast<const CurveTo *>(other);

  if (that)
    return approxEqual(m_x1, that->m_x1, eps) && approxEqual(m_y1, that->m_y1, eps)
           && approxEqual(m_x2, that->m_x2, eps) && approxEqual(m_y2, that->m_y2, eps)
           && approxEqual(m_x, that->m_x, eps) && approxEqual(m_y, that->m_y, eps)
           ;

  return false;
}

void CurveTo::transform(const glm::dmat3 &tr)
{
  glm::dvec3 vec = tr * glm::dvec3(m_x, m_y, 1);

  m_x = vec[0];
  m_y = vec[1];

  vec = tr * glm::dvec3(m_x1, m_y1, 1);

  m_x1 = vec[0];
  m_y1 = vec[1];

  vec = tr * glm::dvec3(m_x2, m_y2, 1);

  m_x2 = vec[0];
  m_y2 = vec[1];

}

void CurveTo::write(RVNGPropertyList &element) const
{
  element.insert("librevenge:path-action", "C");
  element.insert("svg:x", pt2in(m_x));
  element.insert("svg:y", pt2in(m_y));
  element.insert("svg:x1", pt2in(m_x1));
  element.insert("svg:y1", pt2in(m_y1));
  element.insert("svg:x2", pt2in(m_x2));
  element.insert("svg:y2", pt2in(m_y2));
}

}

IWORKPath::Element::~Element()
{
}

IWORKPath::IWORKPath()
  : m_elements()
  , m_closed(false)
{
}

IWORKPath::IWORKPath(const std::string &path)
  : m_elements()
  , m_closed(false)
{
  namespace ascii = boost::spirit::ascii;
  namespace qi = boost::spirit::qi;

  using boost::phoenix::at_c;
  using boost::phoenix::bind;
  using qi::double_;

  const qi::rule<string::const_iterator, ascii::space_type> rule =
    +(
      ('C' >> double_ >> double_ >> double_ >> double_ >> double_ >> double_)[bind(&IWORKPath::appendCurveTo, this, qi::_1, qi::_2, qi::_3, qi::_4, qi::_5, qi::_6)]
      | ('M' >> double_ >> double_)[bind(&IWORKPath::appendMoveTo, this, qi::_1, qi::_2)]
      | ('L' >> double_ >> double_)[bind(&IWORKPath::appendLineTo, this, qi::_1, qi::_2)]
      | qi::char_('Z')[bind(&IWORKPath::appendClose, this)]
    )
    ;

  string::const_iterator it = path.begin();
  const bool r = qi::phrase_parse(it, path.end(), rule, ascii::space);

  if (!r || (path.end() != it))
  {
    ETONYEK_DEBUG_MSG(("parsing of path '%s' failed\n", path.c_str()));
    throw InvalidException();
  }
}

IWORKPath::IWORKPath(const IWORKPath &other)
  : m_elements()
  , m_closed(other.m_closed)
{
  try
  {
    for (std::deque<Element *>::const_iterator it = other.m_elements.begin(); it != other.m_elements.end(); ++it)
      m_elements.push_back((*it)->clone());
  }
  catch (...)
  {
    clear();
    throw;
  }
}

IWORKPath::~IWORKPath()
{
  clear();
}

IWORKPath &IWORKPath::operator=(const IWORKPath &other)
{
  IWORKPath copy(other);
  swap(copy);
  return *this;
}

void IWORKPath::swap(IWORKPath &other)
{
  using std::swap;
  swap(m_elements, other.m_elements);
}

void IWORKPath::clear()
{
  for (std::deque<Element *>::const_iterator it = m_elements.begin(); it != m_elements.end(); ++it)
    delete *it;
  m_elements.clear();
}

void IWORKPath::appendMoveTo(const double x, const double y)
{
  if (!m_closed)
    m_elements.push_back(new MoveTo(x, y));
}

void IWORKPath::appendLineTo(const double x, const double y)
{
  m_elements.push_back(new LineTo(x, y));
}

void IWORKPath::appendCurveTo(const double x1, const double y1, const double x2, const double y2, const double x, const double y)
{
  m_elements.push_back(new CurveTo(x1, y1, x2, y2, x, y));
}

void IWORKPath::appendClose()
{
  m_closed = true;
}

void IWORKPath::operator*=(const glm::dmat3 &tr)
{
  for_each(m_elements.begin(), m_elements.end(), boost::bind(&Element::transform, _1, cref(tr)));
}

void IWORKPath::write(librevenge::RVNGPropertyListVector &vec) const
{
  for (std::deque<Element *>::const_iterator it = m_elements.begin(); m_elements.end() != it; ++it)
  {
    RVNGPropertyList element;
    (*it)->write(element);
    vec.append(element);
  }

  if (m_closed)
  {
    librevenge::RVNGPropertyList element;
    element.insert("librevenge:path-action", "Z");
    vec.append(element);
  }
}

bool approxEqual(const IWORKPath &left, const IWORKPath &right, const double eps)
{
  return left.m_elements.size() == right.m_elements.size()
         && std::equal(left.m_elements.begin(), left.m_elements.end(), right.m_elements.begin(),
                       boost::bind(&IWORKPath::Element::approxEqualsTo, _1, _2, eps))
         ;
}

bool operator==(const IWORKPath &left, const IWORKPath &right)
{
  return approxEqual(left, right);
}

bool operator!=(const IWORKPath &left, const IWORKPath &right)
{
  return !(left == right);
}

IWORKPath operator*(const IWORKPath &path, const glm::dmat3 &tr)
{
  IWORKPath newPath(path);
  newPath *= tr;
  return newPath;
}

}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
