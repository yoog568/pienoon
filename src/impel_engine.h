// Copyright 2014 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef IMPEL_ENGINE_H_
#define IMPEL_ENGINE_H_

#include <map>

#include "impel_common.h"

namespace impel {


class ImpelProcessorBase;
struct ImpelProcessorFunctions;

// The engine holds all of the processors, and updates them all when
// AdvanceFrame() is called. The processing is kept central, in this manner,
// for scalability. The engine is not a singleton, but you should try to
// minimize the number of engines in your game. As more Impellers are added to
// the processors, you start to get economies of scale.
class ImpelEngine {
  typedef std::map<ImpellerType, ImpelProcessorBase*> Map;
  typedef std::pair<ImpellerType, ImpelProcessorBase*> Pair;
  typedef std::map<ImpellerType, ImpelProcessorFunctions> FunctionMap;
  typedef std::pair<ImpellerType, ImpelProcessorFunctions> FunctionPair;
 public:
  void Reset();
  ImpelProcessorBase* Processor(ImpellerType type);
  void AdvanceFrame(ImpelTime delta_time);

  static void RegisterProcessorFactory(ImpellerType type,
                                       const ImpelProcessorFunctions& fns);

 private:
  // Map from the ImpellerType to the ImpelProcessor. Only one ImpelProcessor
  // per type per engine. This is to maximize centralization of data.
  Map processors_;

  // Map from the ImpellerType to the factory that creates the ImpelProcessor.
  // We only create an ImpelProcessor when one is needed.
  static FunctionMap function_map_;
};


} // namespace impel

#endif // IMPEL_ENGINE_H_
