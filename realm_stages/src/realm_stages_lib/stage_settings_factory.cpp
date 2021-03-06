/**
* This file is part of OpenREALM.
*
* Copyright (C) 2018 Alexander Kern <laxnpander at gmail dot com> (Braunschweig University of Technology)
* For more information see <https://github.com/laxnpander/OpenREALM>
*
* OpenREALM is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* OpenREALM is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with OpenREALM. If not, see <http://www.gnu.org/licenses/>.
*/

#include <realm_stages/stage_settings_factory.h>
#include <realm_stages/stage_settings.h>

using namespace realm;

StageSettings::Ptr StageSettingsFactory::load(const std::string &stage_type_set,
                                              const std::string &filepath)
{
  auto settings = std::make_shared<StageSettings>();
  std::string stage_type_read = settings->sneakParamFromFile<std::string>("type", filepath);
  if (stage_type_set != stage_type_read)
    throw(std::invalid_argument("Error: Could not load stage settings. Stage type mismatch!"));

  // Desired stage type and settings file match, start loading file
  if (stage_type_set == "pose_estimation")
    return loadDefault<PoseEstimationSettings>(settings, stage_type_set, filepath);
  if (stage_type_set == "densification")
    return loadDefault<DensificationSettings>(settings, stage_type_set, filepath);
  if (stage_type_set == "surface_generation")
    return loadDefault<SurfaceGenerationSettings>(settings, stage_type_set, filepath);
  if (stage_type_set == "ortho_rectification")
    return loadDefault<OrthoRectificationSettings>(settings, stage_type_set, filepath);
  if (stage_type_set == "mosaicing")
    return loadDefault<MosaicingSettings>(settings, stage_type_set, filepath);
}

template <typename T>
StageSettings::Ptr StageSettingsFactory::loadDefault(StageSettings::Ptr settings,
                                                     const std::string &stage_type_set,
                                                     const std::string &filepath)
{
  settings = std::make_shared<T>();
  settings->loadFromFile(filepath);
  return std::move(settings);
}