/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef incl_HPHP_PARAMETER_EXPRESSION_H_
#define incl_HPHP_PARAMETER_EXPRESSION_H_

#include <compiler/expression/expression.h>
#include <util/json.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

DECLARE_BOOST_TYPES(Type);
DECLARE_BOOST_TYPES(AnalysisResult);
DECLARE_BOOST_TYPES(ParameterExpression);
DECLARE_BOOST_TYPES(TypeAnnotation);

class ParameterExpression : public Expression {
public:
  ParameterExpression(EXPRESSION_CONSTRUCTOR_PARAMETERS,
                      TypeAnnotationPtr type, const std::string &name,
                      bool ref, ExpressionPtr defaultValue,
                      ExpressionPtr attributeList);

  DECLARE_EXPRESSION_VIRTUAL_FUNCTIONS;

  bool isRef() const { return m_ref;}
  bool isOptional() const { return m_defaultValue;}
  const std::string &getName() const { return m_name; }
  int getLocalEffects() const { return NoEffect; }
  void rename(const std::string &name) { m_name = name;}
  ExpressionPtr defaultValue() { return m_defaultValue; }
  ExpressionPtr userAttributeList() { return m_attributeList; }
  TypePtr getTypeSpec(AnalysisResultPtr ar, bool forInference);
  bool hasTypeHint() const { return !m_type.empty(); }
  const std::string &getTypeHint() const {
    assert(hasTypeHint());
    return m_type;
  }
  bool hasUserType() const { return m_originalType != nullptr; }
  const std::string getOriginalTypeHint() const;
  const std::string getUserTypeHint() const;
  void parseHandler(ClassScopePtr cls);
  void compatibleDefault();
  void fixupSelfAndParentTypehints(ClassScopePtr cls);
private:
  TypePtr getTypeSpecForClass(AnalysisResultPtr ar, bool forInference);

  std::string m_type;
  TypeAnnotationPtr m_originalType;
  std::string m_name;
  bool m_ref;
  ExpressionPtr m_defaultValue;
  ExpressionPtr m_attributeList;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // incl_HPHP_PARAMETER_EXPRESSION_H_
